#include "spmvoperation.h"
#include <QDataStream>
#include <QFile>
#include <QDebug>

SpMVOperation::SpMVOperation(QString matrixName)
{

    // only retrieving dense vector access pattern for now

    QFile f(getMatrixFilename(matrixName));
    f.open(QIODevice::ReadOnly);

    // read matrix dimensions
    f.read((char*)&m_rowCount, COLIND_SIZE);
    f.read((char*)&m_colCount, COLIND_SIZE);
    f.read((char*)&m_nzCount, COLIND_SIZE);

    // read in the col indices
    m_colIndices = new quint32[m_nzCount];
    f.read((char *)m_colIndices, m_nzCount * COLIND_SIZE);

    f.close();
}

SpMVOperation::~SpMVOperation()
{
    delete [] m_colIndices;
}

QList<VectorIndex> SpMVOperation::getDVAccessPattern(quint32 peID, quint32 peCount, bool useInterleavedMapping)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    quint32 elementsPerPE = m_nzCount / peCount;
    QList<VectorIndex> indices;

    for(quint32 i = 0; i < elementsPerPE; i++)
    {
        if(useInterleavedMapping)
            indices.push_back(m_colIndices[peID + i * peCount]);
        else
            indices.push_back(m_colIndices[peID*elementsPerPE + i]);
    }

    return indices;
}
