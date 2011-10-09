#ifndef __PROGRESS_BAR__
#define __PROGRESS_BAR__

/*
	from MaNGOS
*/

class barGoLink
{
    static char const * const empty;
    static char const * const full;

    unsigned int rec_no;
    unsigned int rec_pos;
    unsigned int num_rec;
    unsigned int indic_len;

    public:

        void step( void );
        barGoLink( unsigned int );
        ~barGoLink();
};
#endif
