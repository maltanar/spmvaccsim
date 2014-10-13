#ifndef FIFOOUTBREAKOUT_H
#define FIFOOUTBREAKOUT_H

#include "systemc.h"

template <class T>
class FIFOOutBreakout : public sc_module
{
    SC_HAS_PROCESS(FIFOOutBreakout);

public:
    sc_fifo_out<T> fifoOutput;

    FIFOOutBreakout(sc_module_name nm) : sc_module(nm)
    {
        SC_METHOD(fifoOutputAdapt);
        sensitive << fifoOutput.data_read() << m_valid;
        dont_initialize();
    }

    void bindSignalInterface(sc_out<bool> & valid, sc_in<bool> & ready, sc_out<T> & data)
    {
        valid.bind(m_valid);
        ready.bind(m_ready);
        data.bind(m_data);
    }

    void bindFIFOOutput(sc_fifo_out<T> & fifoOut)
    {
        fifoOut.bind(fifoOutput);
    }

    void fifoOutputAdapt()
    {
        m_ready = (fifoOutput.num_free() > 0);

        if(fifoOutput.num_free() > 0 && m_valid)
        {
            sc_assert(fifoOutput.nb_write(m_data));
        }
    }

protected:
    sc_signal<bool> m_valid;
    sc_signal<bool> m_ready;
    sc_signal<T> m_data;

};



#endif // FIFOOUTBREAKOUT_H
