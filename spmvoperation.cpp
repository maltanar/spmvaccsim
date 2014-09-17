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

    // read in the row lengths
    m_rowPointers = new quint32[m_rowCount + 1];
    f.read((char *)m_rowPointers, (m_rowCount + 1) * COLIND_SIZE);

    f.close();
}

SpMVOperation::~SpMVOperation()
{
    delete [] m_colIndices;
    delete [] m_rowPointers;
}

QList<VectorIndex> SpMVOperation::getDVAccessPattern(quint32 peID, quint32 peCount, bool useInterleavedMapping)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    // TODO distribute nonzeroes  according to row lengths (they are not uniform)
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

QList<quint32> SpMVOperation::getRowLengths(quint32 peID, quint32 peCount, bool useInterleavedMapping)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    quint32 rowsPerPE = m_rowCount / peCount;
    QList<quint32> rowLengths;

    for(quint32 i = 0; i < rowsPerPE; i++)
    {
        int row = 0;
        if(useInterleavedMapping)
            row = peID + i * peCount;
        else
            row = peID*rowsPerPE + i;

        rowLengths.push_back(m_rowPointers[row+1] - m_rowPointers[row]);
    }

    return rowLengths;
}
