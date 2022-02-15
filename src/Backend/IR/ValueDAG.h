#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Backend/IR/Value.h"
#include "Backend/IR/Instruction.h"
#include "Backend/IR/BasicBlock.h"
#include "ADT/graphs.h"
#include "ADT/dlink.h"

namespace IR {

	/// <summary>
	/// ��ô�����ͼ������������,������㷨������
	/// 1. Ѱ�ҹ����ӱ��ʽ
	/// 2. ��������ָ��
	/// </summary>
	class ValueDAG {
	public:
		class Node  :public ADT::d_link<Node> {
		public:
			Value* getValue() const {
				return m_value;
			}
			Node() 
				: ADT::d_link<Node>()
			{}
			Node(Value* v) 
				: ADT::d_link<Node>()
				, m_value( v )
			{}
		private:
			Value* m_value;
		};
		static std::shared_ptr<ValueDAG> makeValueDAG( BasicBlock* BB  );
		ADT::adjacency_list<std::set, IR::ValueDAG::Node>& getAdjacency_list() {
			return m_dag;
		}
		IR::BasicBlock* getBasicBlock() const {
			return m_BB;
		}
		
		
	
	private:

	private:
		IR::BasicBlock* m_BB;
		ADT::adjacency_list<std::set,IR::ValueDAG::Node> m_dag;


	};

}