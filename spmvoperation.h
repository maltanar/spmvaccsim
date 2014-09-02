#ifndef SPMVOPERATION_H
#define SPMVOPERATION_H

#include <QString>
#include <QList>
#include "utilities.h"

#define COLIND_SIZE     sizeof(quint32)


class SpMVOperation
{
public:
    SpMVOperation(QString matrixName);
    ~SpMVOperation();

    quint32 rowCount() {return m_rowCount;}
    quint32 colCount() {return m_colCount;}
    quint32 nzCount() {return m_nzCount;}

    QList<VectorIndex> getDVAccessPattern(quint32 peID, quint32 peCount, bool useInterleavedMapping=false);


protected:
    QString m_matrixName;
    quint32 m_rowCount, m_colCount, m_nzCount;
    quint32 * m_colIndices;

};

#endif // SPMVOPERATION_H
