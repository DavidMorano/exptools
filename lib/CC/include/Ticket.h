#ifndef TICKET_DOT_H
#define TICKET_DOT_H

/*N is name, F is friend class*/

PT_define Ticketdeclare(N,F)
class N {
friend F;
static const int bits_increment;
static Bits b;
int num;
public:
	N() : num(-1) {}
	void validate();
	void invalidate();
	~N() {}
};
PT_end

PT_define Ticketimplement(N,F)
const int N::bits_increment = sizeof(unsigned long); 
		//should be ok for most machines
Bits N::b = Bits(0, N::bits_increment);
void N::validate() {
	int count = 0;
	while (b[count])
		count++;
	while (count >= b.size())
		b.size(b.size() + N::bits_increment);
	num = count;
	b.set(num);
	}
void N::invalidate() {
	b.reset(num);
	}
PT_end
#endif
