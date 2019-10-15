typedef struct {
    int route[43];      // 43 p/ caso max.
    unsigned int cost;  // Custo do percurso
} route;

typedef route element;
typedef route stack_element;

#include "..\lib\dyn_queue.h"
#include "..\lib\stackld.h"

int size = 42;     // Tamanho da matriz
int **adj_matrix;  // Matriz de adjacência

/**
 * /INDICES POR REGIAO /
 *
 * NOROESTE     NORDESTE
 * [00-08]      [30-41]
 *
 * SUDOESTE     SUDESTE
 * [09-17]      [18-29]
 */
static char locations[42][20] = {
    /*00*/ {"Boise"},
    /*01*/ {"Denver"},
    /*02*/ {"Lake Tahoe"},
    /*03*/ {"Portland"},
    /*04*/ {"Salt Lake City"},
    /*05*/ {"San Francisco"},
    /*06*/ {"Seatle"},
    /*07*/ {"Vail"},
    /*08*/ {"Yellowstone"},
    /*09*/ {"Albuquerque"},
    /*10*/ {"Aspen"},
    /*11*/ {"Colorado Springs"},
    /*12*/ {"Grand Canyon"},
    /*13*/ {"Las Vegas"},
    /*14*/ {"Los Angeles"},
    /*15*/ {"Palm Springs"},
    /*16*/ {"Phoenix"},
    /*17*/ {"San Diego"},
    /*18*/ {"Atlanta"},
    /*19*/ {"Dallas"},
    /*20*/ {"Fort Lauderdale"},
    /*21*/ {"Houston"},
    /*22*/ {"Little Rock"},
    /*23*/ {"Memphis"},
    /*24*/ {"Miami"},
    /*25*/ {"Nashville"},
    /*26*/ {"Nova Orleans"},
    /*27*/ {"Orlando"},
    /*28*/ {"San Antonio"},
    /*29*/ {"St. Louis"},
    /*30*/ {"Albany"},
    /*31*/ {"Boston"},
    /*32*/ {"Chicago"},
    /*33*/ {"Detroit"},
    /*34*/ {"Indianopolis"},
    /*35*/ {"Kansas City"},
    /*36*/ {"Milwaukee"},
    /*37*/ {"Minneapolis"},
    /*38*/ {"Nova York"},
    /*39*/ {"Omaha"},
    /*40*/ {"Richmond"},
    /*41*/ {"Washington"}};