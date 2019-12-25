/*+==================================================================
* CopyRight (c) 2019 icerlion
* All rights reserved
* This program is UNPUBLISHED PROPRIETARY property.
* Only for internal distribution.
*
* FileName: AhoCorasick.hpp
*
* Purpose:  Implement Aho Corasick Algorithm
*
* Author:   JhonFrank(icerlion@163.com)
*
* Modify:   2019/12/24 16:31
==================================================================+*/
#ifndef _AHOCORASICK_H_
#define _AHOCORASICK_H_
#include <map>
#include <vector>
#include <string>
#include <set>
#include <assert.h>
#include <algorithm>

class CAhoCorasick
{
private:
#define CONTINUE_ON_NULLPTR(POINTER) if (nullptr == POINTER) { assert(false); continue; }
#define BREAK_ON_NULLPTR(POINTER) if (nullptr == POINTER) { assert(false); break; }
#define RETURN_ON_NULLPTR(POINTER, RETVAL) if (nullptr == POINTER) { assert(false); return RETVAL; }
    // Define state node
    typedef struct StateNode
    {
        StateNode()
            :nNodeId(),
            nStateValue(0),
            nHeight(0),
            pParentNode(nullptr),
            pRedirectNode(nullptr),
            bOutputFlag(false)
        {
        }
        int nNodeId;
        char nStateValue;
        std::map<char, StateNode*> mapChildNode;
        int nHeight;
        StateNode* pParentNode;
        StateNode* pRedirectNode;
        bool bOutputFlag;
    } StateNode;

public:
    CAhoCorasick(bool bCaseSensitive = true)
        :m_bCaseSensitive(bCaseSensitive),
        m_nNextNodeId(-1),
        m_pRootNode(nullptr)
    {
        m_pRootNode = CreateStateNode(0, nullptr, 0);
        m_pRootNode->pRedirectNode = m_pRootNode;
    }

    ~CAhoCorasick()
    {
        for (StateNode* pNode : m_vecStateNode)
        {
            delete pNode;
        }
        m_pRootNode = nullptr;
        m_mapStateNode.clear();
        m_vecStateNode.clear();
    }

    inline bool AddWord(const std::string& strValue)
    {
        int nHeight = 0;
        std::set<char> setHitStateValue;
        StateNode* pCurNode = m_pRootNode;
        for (char nCurState : strValue)
        {
            nCurState = FixStateValue(nCurState);
            setHitStateValue.insert(nCurState);
            ++nHeight;
            BREAK_ON_NULLPTR(pCurNode);
            auto itFind = pCurNode->mapChildNode.find(nCurState);
            if (itFind == pCurNode->mapChildNode.end())
            {
                pCurNode = CreateStateNode(nCurState, pCurNode, nHeight);
            }
            else
            {
                pCurNode = itFind->second;
            }
        }
        RETURN_ON_NULLPTR(pCurNode, false);
        pCurNode->bOutputFlag = true;
        return true;
    }

    inline void RefreshRedirectState()
    {
        std::set<char> setState;
        for (auto& kvp : m_mapStateNode)
        {
            setState.insert(kvp.first);
        }
        BuildRedirectState(setState);
    }

    // Return true if there has pattern match the input string, faster then SearchPattern
    inline bool MatchPattern(const std::string& strInput) const
    {
        bool bResult = false;
        StateNode* pCurNode = m_pRootNode;
        for (char nCurState : strInput)
        {
            nCurState = FixStateValue(nCurState);
            while (true)
            {
                BREAK_ON_NULLPTR(pCurNode);
                auto itFind = pCurNode->mapChildNode.find(nCurState);
                if (itFind == pCurNode->mapChildNode.end())
                {
                    if (pCurNode == m_pRootNode)
                    {
                        break;
                    }
                    BREAK_ON_NULLPTR(pCurNode);
                    pCurNode = pCurNode->pRedirectNode;
                }
                else
                {
                    pCurNode = itFind->second;
                    BREAK_ON_NULLPTR(pCurNode);
                    if (pCurNode->bOutputFlag)
                    {
                        bResult = true;
                    }
                    break;
                }
            }
            if (bResult)
            {
                break;
            }
        }
        return bResult;
    }

    // Output all search result
    inline std::set<std::string> SearchPattern(const std::string& strInput) const
    {
        std::set<std::string> setResult;
        StateNode* pCurNode = m_pRootNode;
        for (char nCurState : strInput)
        {
            nCurState = FixStateValue(nCurState);
            while (true)
            {
                BREAK_ON_NULLPTR(pCurNode);
                auto itFind = pCurNode->mapChildNode.find(nCurState);
                if (itFind == pCurNode->mapChildNode.end())
                {
                    BREAK_ON_NULLPTR(pCurNode);
                    if (pCurNode == m_pRootNode)
                    {
                        break;
                    }
                    pCurNode = pCurNode->pRedirectNode;
                }
                else
                {
                    pCurNode = itFind->second;
                    BREAK_ON_NULLPTR(pCurNode);
                    if (pCurNode->bOutputFlag)
                    {
                        setResult.insert(BuildOutputString(pCurNode));
                    }
                    break;
                }
            }
        }
        return setResult;
    }

private:
    inline void BuildRedirectState(const std::set<char>& setStateValue)
    {
        for (char chCurState : setStateValue)
        {
            auto itFind = m_mapStateNode.find(chCurState);
            if (itFind == m_mapStateNode.end())
            {
                assert(false);
                continue;
            }
            const std::set<StateNode*>& setStateNode = itFind->second;
            for (StateNode* pBaseNode : setStateNode)
            {
                for (StateNode* pRedirectNode : setStateNode)
                {
                    TryRefreshRedirectNode(pBaseNode, pRedirectNode);
                }
            }
        }
    }

    inline bool TryRefreshRedirectNode(StateNode* pBaseNode, StateNode* pRedirectNode)
    {
        RETURN_ON_NULLPTR(pBaseNode, false);
        RETURN_ON_NULLPTR(pRedirectNode, false);
        if (pBaseNode->nHeight <= pRedirectNode->nHeight)
        {
            return false;
        }
        bool bResult = true;
        StateNode* pBaseCursor = pBaseNode;
        StateNode* pRedirectCursor = pRedirectNode;
        while (m_pRootNode != pRedirectCursor)
        {
            BREAK_ON_NULLPTR(pBaseCursor);
            BREAK_ON_NULLPTR(pRedirectCursor);
            if (FixStateValue(pBaseCursor->nStateValue) != FixStateValue(pRedirectCursor->nStateValue))
            {
                bResult = false;
                break;
            }
            pBaseCursor = pBaseCursor->pParentNode;
            pRedirectCursor = pRedirectCursor->pParentNode;
        }
        if (bResult)
        {
            RETURN_ON_NULLPTR(pBaseNode->pRedirectNode, false);
            RETURN_ON_NULLPTR(pRedirectNode, false);
            if (pBaseNode->pRedirectNode->nHeight < pRedirectNode->nHeight)
            {
                pBaseNode->pRedirectNode = pRedirectNode;
            }
        }
        return bResult;
    }

    inline StateNode* CreateStateNode(char chStateValue, StateNode* pParentNode, int nHeight)
    {
        StateNode* pStateNode = new StateNode();
        pStateNode->bOutputFlag = false;
        pStateNode->nStateValue = chStateValue;
        pStateNode->nHeight = nHeight;
        pStateNode->nNodeId = ++m_nNextNodeId;
        pStateNode->pParentNode = pParentNode;
        pStateNode->pRedirectNode = m_pRootNode;
        if (nullptr != pParentNode)
        {
            pParentNode->mapChildNode.insert(std::make_pair(chStateValue, pStateNode));
        }
        auto itFind = m_mapStateNode.find(chStateValue);
        if (itFind == m_mapStateNode.end())
        {
            std::set<StateNode*> setInner;
            setInner.insert(pStateNode);
            m_mapStateNode.insert(std::make_pair(chStateValue, setInner));
        }
        else
        {
            std::set<StateNode*>& setInner = itFind->second;
            setInner.insert(pStateNode);
        }
        m_vecStateNode.push_back(pStateNode);
        return pStateNode;
    }

    inline std::string BuildOutputString(StateNode* pNode) const
    {
        std::string strResult;
        RETURN_ON_NULLPTR(pNode, strResult);
        strResult.reserve(pNode->nHeight);
        while (nullptr != pNode && pNode->pParentNode != nullptr)
        {
            strResult.push_back(pNode->nStateValue);
            pNode = pNode->pParentNode;
            BREAK_ON_NULLPTR(pNode);
        }
        std::reverse(strResult.begin(), strResult.end());
        return strResult;
    }

    inline char FixStateValue(char chValue) const
    {
        if (m_bCaseSensitive)
        {
            return chValue;
        }
        if (chValue >= 'A' && chValue <= 'Z')
        {
            return chValue + ('a' - 'A') ;
        }
        return chValue;
    }

private:
    bool m_bCaseSensitive;
    int m_nNextNodeId;
    StateNode* m_pRootNode;
    // Key: state value
    // Value: set of node which has the same state value
    std::map<char, std::set<StateNode*> > m_mapStateNode;
    std::vector<StateNode*> m_vecStateNode;
};

#endif // _AHOCORASICK_H_
