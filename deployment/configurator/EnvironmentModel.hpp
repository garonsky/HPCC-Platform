#ifndef _ENVIRONMENT_MODEL_HPP_
#define _ENVIRONMENT_MODEL_HPP_

#include <cassert>

class CXSDNodeBase;
class CEnvironmentModelNode;
class PointerArray;

template <class TYPE>
class CIArrayOf;

class CEnvironmentModelNode
{
public:

    CEnvironmentModelNode(const CEnvironmentModelNode *pParent = 0, int index = 0);
    virtual ~CEnvironmentModelNode();

    int getNumberOfChildren() const;

    const CXSDNodeBase* getXSDNode() const
    {
        return m_pXSDNode;
    }

    CEnvironmentModelNode* getParent()
    {
        return m_pParent;
    }

    CEnvironmentModelNode* getChild(int index);

protected:

    CXSDNodeBase *m_pXSDNode;
    CEnvironmentModelNode *m_pParent;
    //CIArrayOf<CEnvironmentModelNode*> *m_pArrChildNodes;
    PointerArray *m_pArrChildNodes;
} __attribute__((aligned (32)));

class CEnvironmentModel
{
public:

    static CEnvironmentModel* getInstance();

    virtual ~CEnvironmentModel();

    CEnvironmentModelNode* getParent(CEnvironmentModelNode *pChild);
    CEnvironmentModelNode* getChild(CEnvironmentModelNode *pParent, int index);

    CEnvironmentModelNode* getRoot()
    {
        assert(m_pRootNode != 0);

        return m_pRootNode;
    }
    const char* getData(CEnvironmentModelNode *pChild);

protected:

    CEnvironmentModel();
    CEnvironmentModelNode *m_pRootNode;
};

#endif // _ENVIRONMENT_MODEL_HPP_
