#include "Backend/IR/ValueDAG.h"
#include "Backend/IR/BasicBlock.h"
#include <map>

namespace IR {
	/// <summary>
	/// 1. 我们可以允许代码不够高效,但是我们必须做到一点就是代码易于维护,算法的步骤一定要很强
	/// </summary>
	/// <param name="BB"></param>
	/// <returns></returns>
	std::shared_ptr<ValueDAG> ValueDAG::makeValueDAG( BasicBlock*BB) {
		ADT::graph::adjacency_list<IR::ValueDAG::Node> G;
        using vertex = ADT::graph::adjacency_list<IR::ValueDAG::Node>::vertex;
        std::map<Value*, vertex> valueVertexMap;
        
        for (auto ins = BB->begin(); ins != BB->end(); ins = ins->getNext()) {

            if (true == Instruction::isUnaryOp(ins->getOpCode())) {
                IR::UnaryOpIns const* unaryIns = static_cast<IR::UnaryOpIns const*>(ins);
                Value* r = unaryIns->getRetValue();
                vertex vr = nullptr;
                /// 1.对于结果节点,我们一定会新建节点
                {
                    vr = G.add_vertex( r );

                    auto iter = valueVertexMap.find( r );
                    if (iter != valueVertexMap.end()) {
                        iter->second->data().insertBack(&vr->data());
                        valueVertexMap.erase(iter);
                    }
                    valueVertexMap.insert(std::make_pair( r,vr ));
                }
                

                Value* v = unaryIns->getFirstOperand();
                
                auto iter = valueVertexMap.find(v);
                if (iter == valueVertexMap.end()) { 
                    vertex vv1 = G.add_vertex(v);
                    valueVertexMap.insert(std::make_pair(v, vv1));
                    G.add_edge(vr, vv1);
                }
                else {
                    G.add_edge(vr, iter->second);
                }
            }
            else if (true == Instruction::isBinaryOp(ins->getOpCode())) {
                IR::BinaryOpIns const* binaryIns = static_cast<IR::BinaryOpIns const*>(ins);
                Value* r = binaryIns->getRetValue();
                vertex vr = nullptr;
                /// 1.对于结果节点,我们一定会新建节点
                {
                    vr = G.add_vertex(r);
                    auto iter = valueVertexMap.find( r );
                    if (iter != valueVertexMap.end()) {
                        iter->second->data().insertBack(&vr->data());
                        valueVertexMap.erase(iter);
                    }
                    valueVertexMap.insert(std::make_pair(r, vr));
                }


                Value* v1 = binaryIns->getFirstOperand();

                auto iter = valueVertexMap.find(v1);
                if (iter == valueVertexMap.end()) {
                    ADT::graph::adjacency_list<IR::ValueDAG::Node>::vertex vv1 = G.add_vertex(v1);
                    valueVertexMap.insert(std::make_pair(v1, vv1));
                    G.add_edge(vr, vv1);
                }
                else {
                    G.add_edge(vr, iter->second);
                }

                Value* v2 = binaryIns->getSecondOperand();
                iter = valueVertexMap.find(v2);
                if (iter == valueVertexMap.end()) {
                    ADT::graph::adjacency_list<IR::ValueDAG::Node>::vertex vv2 = G.add_vertex(v2);
                    valueVertexMap.insert(std::make_pair(v2, vv2));
                    G.add_edge(vr, vv2);
                }
                else {
                    G.add_edge(vr, iter->second);
                }

            }
            else {
                if (Instruction::OpCode::kAssign == ins->getOpCode()) {
                    IR::AssignIns const* unaryIns = static_cast<IR::AssignIns const*>(ins);
                    Value* r = unaryIns->getRetValue();
                    ADT::graph::adjacency_list<IR::ValueDAG::Node>::vertex vr = nullptr;
                    /// 1.对于结果节点,我们一定会新建节点
                    {
                        vr = G.add_vertex(r);
                        auto iter = valueVertexMap.find( r );
                        if (iter != valueVertexMap.end()) {
                            iter->second->data().insertBack(&vr->data());
                            valueVertexMap.erase(iter);
                        }
                        valueVertexMap.insert(std::make_pair(r, vr));
                    }


                    Value* v = unaryIns->getFirstOperand();

                    auto iter = valueVertexMap.find(v);
                    if (iter == valueVertexMap.end()) {
                        ADT::graph::adjacency_list<IR::ValueDAG::Node>::vertex vv1 = G.add_vertex(v);
                        valueVertexMap.insert(std::make_pair(v, vv1));
                        G.add_edge(vr, vv1);
                    }
                    else {
                        G.add_edge(vr, iter->second);
                    }


                }
            }

        }
        std::shared_ptr<ValueDAG> dag = std::make_shared<ValueDAG>();
        dag->m_BB = BB;
        dag->m_dag = std::move(G);
        return dag;
	}
    

}