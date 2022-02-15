#include <sstream>
#include "Backend/IR/FlowGraphs.h"
#include "Backend/IR/Instruction.h"

namespace IR {
	template<typename T, size_t N>
	static constexpr size_t array_size( T(&a)[N]){
		return N;
	}

	template<typename T>
	class order_set {
	public:
		size_t size() const {
			return m_list.size();
		}
		T& operator[](size_t i) {
			return m_list.at(i);
		}
		T& at(size_t i ) {
			return m_list.at(i);
		}
		T const& at(size_t i) const {
			return m_list.at(i);
		}
		T const& operator[](size_t i) const {
			return m_list.at(i);
		}
		void push_back(T const& v) {
			if (m_sets.find(v) == m_sets.end()) {
				m_list.push_back(v);
				m_sets.insert(v);
			}
		}
	private:
		std::vector<T> m_list;
		std::set<T> m_sets;
	};
	/// <summary>
	/// 这个函数很重要
	/// </summary>
	/// <param name="function"></param>
	/// <returns></returns>
	std::shared_ptr<FlowGraphs> FlowGraphs::makeFlowGraphs(Function* function) {

		std::shared_ptr<ADT::adjacency_list<std::set,BasicBlock>> G = std::make_shared<ADT::adjacency_list<std::set,BasicBlock>>();
		auto begin = G->add_vertex(function);
		auto end = G->add_vertex(function);

		begin->data().m_index = 0;
		begin->data().m_bStart = true;
		begin->data().m_bEnd = false;

		end->data().m_bStart = false;
		end->data().m_bEnd = true;

		order_set<Instruction*> leaders;
		
		order_set<Instruction*> ends;
		
		bool bFirstIns = true;
		bool bJmp = false;
		/// <summary>
		/// 1.look up the leader instruction
		/// </summary>
		/// <param name="function"></param>
		/// <returns></returns>
		for (auto ins = function->begin(); ins != function->end(); ins = ins->getNext()) {
			auto OpCode = ins->getOpCode();
			if (true == bFirstIns) { ///1.1 the first instruction is leader instruction
				leaders.push_back(ins);
				bFirstIns = false;
				continue;
			}
			static Instruction::OpCode JmpOpCode[] = {
				Instruction::OpCode::kJmp,
				Instruction::OpCode::kBr,
				Instruction::OpCode::kRet,
			};
			/// 1.2 any jmp instruction is end instruction and the next instruction is leader instruction
			for (size_t i = 0; i < array_size(JmpOpCode); ++i) {
				if (OpCode == JmpOpCode[i]) {
					if (nullptr != ins->getNext()) {
						auto nextIns = ins->getNext();
						if (nextIns != function->end()) {
							leaders.push_back(ins->getNext());
						}
					}
					break;
				}
			}
			/// 1.3 we consider label instruction is a leader instruction
			if (Instruction::OpCode::kLabel == OpCode) {
				leaders.push_back(ins);
			}
			/// the other instruction we consider as the basic instruction
			else {

			}
		}

		for (size_t i = 1; i < leaders.size(); ++i) {
			auto ins = leaders.at(i);
			auto end = ins->getPrev();
			ends.push_back(end);
		}
		ends.push_back( function->last() );


		bFirstIns = true;
		std::vector<ADT::vertex<BasicBlock>* > blocks;
		leaders.push_back(function->end());
		blocks.push_back(begin);
		std::map<std::string, ADT::vertex<BasicBlock>*>  mapBlocks;
		size_t index = 1;
		for (size_t i = 0; i < leaders.size() -1; ++i, ++ index ) {
			auto vertex = G->add_vertex(function);
			if (Instruction::OpCode::kLabel == leaders[i]->getOpCode()) {
				IR::Label* label = static_cast<IR::Label*>(leaders[i]);
				mapBlocks.insert( std::make_pair( label->getLabelName(), vertex ) );
			}
			vertex->data().m_index =  index;
			vertex->data().m_beginIns = leaders[i];
			vertex->data().m_endIns = leaders[i + 1];

			vertex->data().m_firstIns = leaders[i];
			vertex->data().m_lastIns = ends[i];
			
			blocks.push_back(vertex);
		}
		end->data().m_index = index;

		/// <summary>
		///  将块之间的流图建立起来
		/// </summary>
		/// <param name="function"></param>
		/// <returns></returns>
		/// 
		blocks.push_back( end);
		
		for (size_t i = 1; i < blocks.size() - 1; ++i) {
			auto& suc = blocks[i + 1];
			auto& vertex = blocks[i];
			auto ins =vertex->data().last();
			if (Instruction::OpCode::kJmp == ins->getOpCode()) {
				auto* jmpIns = static_cast<Jmp*>(ins);
				std::string label = jmpIns->getJmpLabel( );
				auto iter = mapBlocks.find(label);
				if (iter != mapBlocks.end()) {
					G->add_edge(vertex, iter->second);
				}
			}
			else if (Instruction::OpCode::kBr == ins->getOpCode()) {
				auto* brIns = static_cast<Br*>(ins);
				std::string trueLabel = brIns->getTrueLabel();
				std::string falseLabel = brIns->getFalseLabel();
				auto iter = mapBlocks.find(trueLabel);
				if (iter != mapBlocks.end()) {
					G->add_edge(vertex, iter->second);
				}
				iter = mapBlocks.find(falseLabel);
				if (iter != mapBlocks.end()) {
					G->add_edge(vertex, iter->second);
				}
			}
			else if (Instruction::OpCode::kRet == ins->getOpCode()) {
				G->add_edge(vertex, end);
			}
			else { /// the last ins is not jmp instrucion 
				G->add_edge(vertex, suc);
			}
		}
		G->add_edge(begin, blocks[1]);
		
		/// <summary>
		///  这条逻辑时有问题的
		/// </summary>
		/// <param name="function"></param>
		/// <returns></returns>
		std::shared_ptr<FlowGraphs> flowGraphs = std::make_shared<FlowGraphs>( );
		flowGraphs->m_beginBasicBlock = begin;
		flowGraphs->m_endBasicBlock   = end;
		flowGraphs->m_flowGraph = std::move(*G);
		return flowGraphs;
	}


	std::vector<FlowGraphs::LoopPath> FlowGraphs::_InitLoop(std::vector<BasicBlock*> const& blocks) {
		return std::vector<FlowGraphs::LoopPath>();
	}

}