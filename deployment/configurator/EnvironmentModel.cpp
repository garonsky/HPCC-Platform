#include "EnvironmentModel.hpp"
#include "SchemaCommon.hpp"
#include "ConfigSchemaHelper.hpp"
#include "SchemaMapManager.hpp"
#include "SchemaElement.hpp"
#include "jlib.hpp"

CEnvironmentModelNode::CEnvironmentModelNode(const CEnvironmentModelNode *pParent, int index) : m_pParent(NULL), m_pArrChildNodes(NULL)
{
    if (pParent == NULL)
    {
        m_pArrChildNodes = new PointerArray();

        int nComps = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getNumberOfComponents();
        this->m_pXSDNode = NULL;

        for (int idx = 0; idx < nComps; idx++)
        {
            //CXSDNodeBase *pNode = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx);

            //this->m_pXSDNode = pNode;

            //assert(pNode != NULL);

            CEnvironmentModelNode *pModelNode = new CEnvironmentModelNode(this, idx);

            //pModelNode->m_pXSDNode = pNode;

            m_pArrChildNodes->append(pModelNode);
        }
    }
    else
    {
        m_pParent = const_cast<CEnvironmentModelNode*>(pParent);

        CElement *pElement = static_cast<CElement*>(m_pParent->m_pXSDNode);

        if (pElement == NULL)
        {
            CXSDNodeBase *pNode = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(index);
            m_pXSDNode = pNode;
        }
        else
        {
            assert(pElement->getNodeType() == XSD_ELEMENT);

            CElementArray *pElementArray = static_cast<CElementArray*>(pElement->getParentNode());

            assert(pElementArray->length() > index);

            m_pXSDNode = &(pElementArray->item(index));
        }
    }
}

CEnvironmentModelNode* CEnvironmentModelNode::getChild(int index)
{
   assert(m_pArrChildNodes == NULL || m_pArrChildNodes->length() > index);

   if (m_pArrChildNodes != NULL)
   {
        CEnvironmentModelNode *pNode = static_cast<CEnvironmentModelNode*>(m_pArrChildNodes->item(index));

        return pNode;
   }

   return NULL;
}

CEnvironmentModelNode::~CEnvironmentModelNode()
{
    delete m_pArrChildNodes;
}

int CEnvironmentModelNode::getNumberOfChildren() const
{
    int nRetVal = 0;

    if (m_pArrChildNodes != NULL)
    {
        nRetVal = m_pArrChildNodes->length();
    }
    else if (m_pArrChildNodes == NULL && m_pXSDNode != NULL && m_pParent != (CEnvironmentModel::getInstance()->getRoot()))
    {
        return 0;
    }
    else
    {
        assert(this->getXSDNode()->getNodeType() == XSD_ELEMENT);

        const CElement *pElement = static_cast<const CElement*>(this->getXSDNode());

        const CElementArray *pElementArray = static_cast<const CElementArray*>(pElement->getConstParentNode());

        assert(pElementArray->getNodeType() == XSD_ELEMENT_ARRAY);

        nRetVal = pElementArray->getCountOfSiblingElements(pElement->getXSDXPath());
    }

    return nRetVal;
}

CEnvironmentModel* CEnvironmentModel::getInstance()
{
    static CEnvironmentModel *s_pCEnvModel = NULL;

    if (s_pCEnvModel == NULL)
    {
        s_pCEnvModel = new CEnvironmentModel();
    }

    return s_pCEnvModel;
}

CEnvironmentModel::CEnvironmentModel()
{
    m_pRootNode = new CEnvironmentModelNode(NULL);
}

CEnvironmentModel::~CEnvironmentModel()
{
    delete m_pRootNode;
}

CEnvironmentModelNode* CEnvironmentModel::getParent(CEnvironmentModelNode *pChild)
{
    if (pChild != NULL)
    {
        return pChild->getParent();
    }

    assert(false);
    return NULL;
}

CEnvironmentModelNode* CEnvironmentModel::getChild(CEnvironmentModelNode *pParent, int index)
{
    assert(index >= 0);

    if (pParent == NULL)
    {
        return m_pRootNode;
    }

    assert(pParent->getNumberOfChildren() > index);

    return pParent->getChild(index);
}

const char* CEnvironmentModel::getData(CEnvironmentModelNode *pChild)
{
    assert(pChild != NULL);

    const CElement *pElement = static_cast<const CElement*>(pChild->getXSDNode());

    //assert(pElement != NULL);

    if (pElement != NULL)
    {
        return pElement->getName();
    }
    else
    {
        //this->getRoot()->get
        return "Environment";
    }
}
