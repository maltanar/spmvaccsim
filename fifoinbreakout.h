#ifndef FIFOINBREAKOUT_H
#define FIFOINBREAKOUT_H

#include "systemc.h"

template <class T>
class FIFOInBreakout : public sc_module
{
    SC_HAS_PROCESS(FIFOInBreakout);

public:
    sc_fifo_in<T> fifoInput;

    sc_in_clk clk;

    FIFOInBreakout(sc_module_name nm) : sc_module(nm)
    {
        SC_CTHREAD(updateValid, clk.pos());
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

    void updateValid()
    {
        T data = (T) 0;
        while(1)
        {
            // if data is available in the FIFO, expose it
            m_valid = (fifoInput.num_available() > 0);

            if(fifoInput.nb_read(data))
            {
                m_data = data;
            }

            // wait for at least 1 clock cycle
            wait(1);

            // if we already put some data there,
            // wait until ready before popping new data from FIFO
            if(m_valid)
                while(!m_ready)
                    wait(1);
        }
    }


protected:
    sc_signal<bool> m_valid;
    sc_signal<bool> m_ready;
    sc_signal<T> m_data;

};



#endif // FIFOINBREAKOUT_H
