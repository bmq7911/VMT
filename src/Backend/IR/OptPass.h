#pragma once
#include <memory>
#include <set>
#include <vector>
#include "Backend/IR/Instruction.h"
#include "Backend/IR/InstructionStream.h"
#include "Backend/IR/BasicBlock.h"
#include "Backend/IR/FlowGraphs.h"


namespace IR {
    class OptPass { /// �������Ƕ����Բ��޶�,Ϊ��һ��Ҫ����������
    public:
        virtual std::shared_ptr<InstructionStream> optimize( std::shared_ptr<InstructionStream> & stream ) = 0;


    };
    /// Ϊ��������Ҫ�̳�,�������������OptPass�������,����ÿ�������OptPass�����������ǲ�һ����
    
    /// 1.�Ż�������ظ���ǩ,���ٱ�ǩ����,�ô���ǰ������IR�ǿ�����ֹ����ʹ��label
    /// 2.ѭ���ĸ������������ȥȷ��ѭ������ֹ����
    class EliminatRedundancyLabelPass: public OptPass {
    public:
        /// 1.����ԭ�������ǳ���ʱ,ȡ���Ǹ�������Ĺ�������,���Ǹ����������ǲ�ͬ��
        /// 2.���ǵĽӿ�֮��ʹ�õ��ǹ�ͬ����,����ʵ��ȴ�õ��˸�������Ĳ�ͬ����,�����˱�Ȼ�����ת�������ɸ���ת����Ĺ���
        /// 3.���ʵĴ���������ǵĽӿڲ���ȷ,����ʹ�ø��������˽������
        /// 4.������std::vector��������ʵ��,���Ǵ�ŵ��� ��ͬ���Զ���,��ʱ�����Ǿ�ֻ�ܴ��ڽӿ�ָ��,������ʹ�ýӿڵ�����ʱ�ͺ���
        ///   ����Ҫ�õ��������������ʱ,����Ͳ��ں���,��β��ܱ������ֶ���(�ƺ��޷�����,��Ϊ�ӿ�û��������Ϣ)
        std::shared_ptr<InstructionStream> optimize(std::shared_ptr<InstructionStream> & stream) override {
            uint32_t startLabel = 0;
            std::vector<std::pair<std::set<uint32_t>, uint32_t>> statisticsLabel;
            std::shared_ptr<IR::InstructionStream> result = std::make_shared<IR::InstructionStream>();
            for (size_t i = 0 ; i < stream->size(); ++i) {
                if ( IR::InstructionType::kLabel == stream->at(i)->getInstructionType()) {
                    std::set<uint32_t> sets;
                    /// ��������������� ʹ���� static_pointer_cast Ҳ���� static_cast ����ת��ʱ��ȷ��������,���ǲ�����
                    /// ���ﱾ����������Ҫ����
                    sets.emplace( std::static_pointer_cast<IR::JmpInstruction>(stream->at(i))->getLabel());
                    size_t k = i + 1; /// k >= i+1
                    for (; k < stream->size(); ++k) {
                        if (IR::InstructionType::kLabel == stream->at(k)->getInstructionType()) {
                            sets.emplace( std::static_pointer_cast<IR::JmpInstruction>(stream->at(i))->getLabel());
                        }
                        else {
                            break;
                        }
                    }
                    std::shared_ptr<IR::Label> label = std::make_shared<IR::Label>( startLabel);
                    statisticsLabel.push_back(std::make_pair(sets, startLabel));

                    result->insert(label);
                    i = k - 1; /// 1. k>=i+1 -> k-1 >=i ���²������Խ�������
                    startLabel++;
                    
                    continue;
                }
                result->insert( stream->at(i));
            }
            for (size_t i = 0; i < result->size(); ++i) {
                if (IR::InstructionType::kJmp == result->at(i)->getInstructionType()) {
                    std::shared_ptr<IR::JmpInstruction> &jmp = std::static_pointer_cast<IR::JmpInstruction>(result->at(i));
                    for (size_t k = 0; k < statisticsLabel.size(); ++k) {
                        if (statisticsLabel[k].first.find(jmp->getLabel()) != statisticsLabel[k].first.end() ) {
                            jmp->setLabel(statisticsLabel[k].second);
                            break;
                        }
                    }
                }
            }
            return result;

        }
    };
    //// ������Ƕ�,����Ͳ�Ӧ�ý���pass
    class BasicBlockGraphsPass : public OptPass {
    public:
        BasicBlockGraphsPass() 
            :m_flowGraphs( std::make_shared<IR::FlowGraphs>())
        {}
        std::shared_ptr<InstructionStream> optimize(std::shared_ptr<InstructionStream> & stream) override {
            stream = EliminatRedundancyLabelPass().optimize(stream);
            stream = _MakeFlowGraphs(stream);
            return stream;
        }
        std::shared_ptr<IR::FlowGraphs>   getFlowGraphs(  ) {
            return m_flowGraphs;
        }
    private:
        /// ���������Ҫ
        std::shared_ptr<InstructionStream> _MakeFlowGraphs( std::shared_ptr<InstructionStream> & stream) {
            std::shared_ptr<InstructionStream> result;
            
            std::shared_ptr<BasicBlock> entryBlock = std::make_shared<IR::BasicBlock>( 0 );
            std::shared_ptr<BasicBlock> leaveBlock = std::make_shared<IR::BasicBlock>( uint32_t(-1) );
            std::shared_ptr<BasicBlock> block = std::make_shared<IR::BasicBlock>(1);
            std::shared_ptr<BasicBlock> lastBlock = entryBlock;

            std::vector<std::shared_ptr<BasicBlock>> flowGraphsblocks;
            std::map<uint32_t, std::shared_ptr<BasicBlock>> mapBlock;
            std::map<std::shared_ptr<BasicBlock>, uint32_t>  jmpBlock;
            for (size_t i = 0; i < stream->size(); ++i) {
                std::shared_ptr<IR::Instruction> &ins = stream->at(i);
                if (IR::InstructionType::kLabel == ins->getInstructionType()) {
                    flowGraphsblocks.push_back(block);
                    lastBlock->setNextBlock(block);
                    lastBlock = block;
                    block = std::make_shared<IR::BasicBlock>(i+1);
                    uint32_t label = std::dynamic_pointer_cast<IR::Label>(ins)->getLabel();
                    mapBlock.insert(std::make_pair(label, block ));
                    block->insert(ins);
                }
                else if (IR::InstructionType::kJmp == ins->getInstructionType()) {
                    flowGraphsblocks.push_back(block);
                    
                    lastBlock->setNextBlock(block);
                    lastBlock = block;

                    block = std::make_shared<IR::BasicBlock>(i+1);
                    uint32_t label = std::dynamic_pointer_cast<IR::JmpInstruction>(ins)->getLabel();
                    jmpBlock.insert(std::make_pair(block, label));
                    block->insert(ins);
                }
                else {
                    block->insert(ins);
                }
            }
            block->setNextBlock(leaveBlock);
            flowGraphsblocks.push_back(block);
            for (auto iter = jmpBlock.begin(); iter != jmpBlock.end(); ++iter) {
                uint32_t label = iter->second;
                auto kter = mapBlock.find(label);
                if (kter != mapBlock.end()) {
                    iter->first->setJmpBlock(kter->second);
                }
            }
            for (auto iter = flowGraphsblocks.begin(); iter != flowGraphsblocks.end(); ++iter) {
                m_flowGraphs->insert(*iter);
            }

            return result;
        }
    private:
        std::shared_ptr<IR::FlowGraphs>  m_flowGraphs;
    };

}