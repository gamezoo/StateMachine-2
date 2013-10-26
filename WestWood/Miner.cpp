//
//  Miner.cpp
//  WestWood
//
//  Created by 林光海 on 13-10-26.
//  Copyright (c) 2013年 林光海. All rights reserved.
//

#include "Miner.h"
#include "State.h"
#include "GoHomeAndSleepTillRested.h"
#include "EnterMineAndDigForNugget.h"
#include "VisitBankAndDepositGold.h"
#include "QuenchThirst.h"

Miner::Miner(int id):BaseGameEntity(id),
                    m_Location(shack),
                    m_iGoldCarried(0),
                    m_iMoneyInBank(0),
                    m_iThirst(0),
                    m_iFatigue(0),
                    m_pCurrentState(GoHomeAndSleepTillRested::Instance())
{

}

void Miner::Update()
{
    m_iThirst += 1;
    if(m_pCurrentState)
    {
        m_pCurrentState->Execute(this);
    }
}

void Miner::ChangeState(State *pNewState)
{
    assert(m_pCurrentState && pNewState);
    m_pCurrentState->Exit(this);
    m_pCurrentState = pNewState;
    m_pCurrentState->Enter(this);
}

location_type Miner::Location() const
{
    return m_Location;
}

void Miner::ChangeLocation(location_type newLocation)
{
    m_Location = newLocation;
}

int Miner::GoldCarried() const
{
    return m_iGoldCarried;
}

void Miner::SetGoldCarried(const int val)
{
    m_iGoldCarried = val;
}

void Miner::AddToGoldCarried(const int val)
{
    m_iGoldCarried += val;
    
    if(m_iGoldCarried < 0) m_iGoldCarried = 0;
}

bool Miner::PocketsFull() const
{
    return m_iGoldCarried >= MaxNuggets;
}

bool Miner::Fatigued() const
{
    if(m_iFatigue > TirednessThreshold)
    {
        return true;
    }
    return false;
}

void Miner::DecreaseFatigue()
{
    m_iFatigue -= 1;
}

void Miner::IncreaseFatigue()
{
    m_iFatigue += 1;
}

int Miner::Wealth() const
{
    return m_iMoneyInBank;
}

void Miner::SetWealth(const int val)
{
    m_iMoneyInBank = val;
}

void Miner::AddToWealth(const int val)
{
    m_iMoneyInBank += val;
    
    if(m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Miner::Thirsty() const
{
    if(m_iThirst >= ThirstLevel)
        return true;
    return false;
}

void Miner::BuyAndDrinkAWhiskey()
{
    m_iThirst = 0;
    m_iMoneyInBank -= 2;
}

