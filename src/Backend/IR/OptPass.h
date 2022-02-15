#pragma once
#include <memory>
#include <set>
#include <vector>
#include "Backend/IR/Instruction.h"
#include "Backend/IR/InstructionStream.h"
#include "Backend/IR/BasicBlock.h"
#include "Backend/IR/FlowGraphs.h"


namespace IR {
    class OptPass { /// 输入我们都可以不限定,为何一定要限制输入呢
    public:
        virtual std::shared_ptr<InstructionStream> optimize( std::shared_ptr<InstructionStream> & stream ) = 0;


    };
    /// 为何我们需要继承,这里我们是想把OptPass抽象出来,可视每个具体的OptPass的输入和输出是不一样的
    
    /// 1.优化过多的重复标签,减少标签数量,好处是前端生成IR是可以无止境的使用label
    /// 2.循环的复杂性在于如何去确定循环的终止条件
    class EliminatRedundancyLabelPass: public OptPass {
    public:
        /// 1.本质原因是我们抽象时,取的是各个对象的共有属性,但是各个对象又是不同的
        /// 2.我们的接口之中使用的是共同属性,但是实现却用到了各个对象的不同属性,导致了必然会存在转换过程由父类转子类的过程
        /// 3.本质的错误就是我们的接口不正确,我们使用各个对象的私有属性
        /// 4.考虑向std::vector等容器的实现,我们存放的是 相同属性对象,这时候我们就只能存在接口指针,当我们使用接口的属性时就合理
        ///   当需要用到各个对象的属性时,这个就不在合理,如何才能避免这种东西(似乎无法避免,因为接口没有子类信息)
        std::shared_ptr<InstructionStream> optimize(std::shared_ptr<InstructionStream> & stream) override {
            uint32_t startLabel = 0;
            std::vector<std::pair<std::set<uint32_t>, uint32_t>> statisticsLabel;
            std::shared_ptr<IR::InstructionStream> result = std::make_shared<IR::InstructionStream>();
            for (size_t i = 0 ; i < stream->size(); ++i) {
                if ( IR::InstructionType::kLabel == stream->at(i)->getInstructionType()) {
                    std::set<uint32_t> sets;
                    /// 这里我们讨厌的是 使用了 static_pointer_cast 也就是 static_cast 这种转换时正确的在这里,但是不合理
                    /// 这里本质上我们需要的是
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
                    i = k - 1; /// 1. k>=i+1 -> k-1 >=i 导致不会出现越界等问题
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
    //// 重这个角度,这个就不应该叫做pass
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
        /// 基本块很重要
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