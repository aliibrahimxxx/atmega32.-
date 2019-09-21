/*
 * macros.h
 *
 * Created: 20/09/2019 07:50:54 م
 *  Author: ali ibrahim
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define SETBIT(R,B) (R|=(1<<B))
#define CLRBIT(R,B) (R&=~(1<<B))
#define TGLBIT(R,B) (R^=(1<<B))
#define GETBIT(R,B) ((R)>>(B)&1)



#endif /* MACROS_H_ */