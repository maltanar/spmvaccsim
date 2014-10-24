#ifndef FIFOINBREAKOUT_H
#define FIFOINBREAKOUT_H

#include "systemc.h"

template <class T>
class FIFOInBreakout : public sc_module
{
    SC_HAS_PROCESS(FIFOInBreakout);

public:
    sc_fifo_in<T> fifoInput;

    FIFOInBreakout(sc_module_name nm) : sc_module(nm)
    {
        SC_METHOD(fifoInputAdapt);
        sensitive << fifoInput.data_written() << m_ready;
        dont_initialize();
    }

    void bindSignalInterface(sc_in<bool> & valid, sc_out<bool> & ready, sc_in<T> & data)
    {
        valid.bind(m_valid);
        ready.bind(m_ready);
        data.bind(m_data);
    }

    void bindFIFOInput(sc_fifo_in<T> & fifoIn)
    {
        fifoInput.bind(fifoIn);
    }

    void fifoInputAdapt()
    {
        m_valid = (fifoInput.num_available() > 0);

        // TODO this will not work properly if e.g ready always follows
        // valid in a combinatorial way

        if(fifoInput.num_available() > 0 && m_ready)
        {
            T data = (T) 0;
            sc_assert(fifoInput.nb_read(data));
            m_data = data;

        }
        else
            m_data = (T) 0;
    }

protected:
    sc_signal<bool> m_valid;
    sc_signal<bool> m_ready;
    sc_signal<T> m_data;

};



#endif // FIFOINBREAKOUT_H
