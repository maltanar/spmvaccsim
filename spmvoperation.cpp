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

void SpMVOperation::assignWorkToWorker(quint32 peID, quint32 peCount, quint32 &startingRow, quint64 &startingNZ, QList<quint32> &dvAccessPattern, QList<quint32> &rowLengths)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    // calculate the assigned NZ range for this PE based on the assigned rows
    quint32 rowsPerPE = m_rowCount / peCount;
    startingRow = peID * rowsPerPE;
    quint32 endRow = (peID + 1) * rowsPerPE;

    for(quint32 i = startingRow; i < endRow; i++)
    {
        // push length of current row
        rowLengths.push_back(m_rowPointers[i+1] - m_rowPointers[i]);
        // push accessed column indices
        for(quint32 j = m_rowPointers[i]; j < m_rowPointers[i+1]; j++)
            dvAccessPattern.push_back(m_colIndices[j]);
    }

    // TODO a better way of distribution is to try to match a number of rows
    // containing NNZ/n elements

    startingNZ = m_rowPointers[startingRow];
}

QList<VectorIndex> SpMVOperation::getDVAccessPattern(quint32 peID, quint32 peCount)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    // calculate the assigned NZ range for this PE based on the assigned rows
    quint32 rowsPerPE = m_rowCount / peCount;
    quint32 startRow = peID * rowsPerPE, endRow = (peID + 1) * rowsPerPE;
    QList<VectorIndex> indices;

    for(quint32 i = startRow; i < endRow; i++)
    {
        for(quint32 j = m_rowPointers[i]; j < m_rowPointers[i+1]; j++)
            indices.push_back(m_colIndices[j]);
    }

    // TODO a better way of distribution is to try to match a number of rows
    // containing NNZ/n elements

    return indices;
}

QList<quint32> SpMVOperation::getRowLengths(quint32 peID, quint32 peCount)
{
    // TODO we don't handle corner cases (uneven division for given PE count) here
    quint32 rowsPerPE = m_rowCount / peCount;
    QList<quint32> rowLengths;

    for(quint32 i = 0; i < rowsPerPE; i++)
    {
        int row = peID*rowsPerPE + i;
        rowLengths.push_back(m_rowPointers[row+1] - m_rowPointers[row]);
    }

    return rowLengths;
}
