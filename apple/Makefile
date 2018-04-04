M_SRCS = \
AsteroidsAppDelegate.m

MM_SRCS = \
AsteroidsView.mm \
CAsteroidsBigRock.mm \
CAsteroidsBigSaucer.mm \
CAsteroidsBullet.mm \
CAsteroidsMediumRock.mm \
CAsteroids.mm \
CAsteroidsObject.mm \
CAsteroidsRock.mm \
CAsteroidsSaucer.mm \
CAsteroidsScore.mm \
CAsteroidsShip.mm \
CAsteroidsSmallRock.mm \
CAsteroidsSmallSaucer.mm \
CLFont.mm \
Apple.mm \
main.mm

M_OBJS  = $(M_SRCS:.m=.o)
MM_OBJS = $(MM_SRCS:.mm=.o)

.SUFFIXES: .mm .m

CFLAGS = \
-I$(HOME)/dev/apple/include \
-I$(HOME)/dev/progs/include

.mm.o:
	g++ -c $< -o $*.o $(CFLAGS)

.m.o:
	gcc -c $< -o $*.o $(CFLAGS)

IAsteroids: $(MM_OBJS) $(M_OBJS)
	g++ -o IAsteroids $(M_OBJS) $(MM_OBJS) -lobjc
