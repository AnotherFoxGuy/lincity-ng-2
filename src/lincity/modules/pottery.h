#define GROUP_POTTERY_COLOUR (red(12))
#define GROUP_POTTERY_COST   1000
#define GROUP_POTTERY_COST_MUL 25
#define GROUP_POTTERY_BUL_COST 1000
#define GROUP_POTTERY_TECH  0
#define GROUP_POTTERY_FIREC 50
#define GROUP_POTTERY_RANGE 0
#define GROUP_POTTERY_SIZE 2

#define POTTERY_ORE_MAKE_GOODS    11
#define POTTERY_COAL_MAKE_GOODS    2
#define POTTERY_JOBS              35
#define POTTERY_MADE_GOODS        35
#define POTTERY_ANIM_SPEED        280
#define POTTERY_CLOSE_TIME        25
#define MAX_ORE_AT_POTTERY        (POTTERY_ORE_MAKE_GOODS*20)
#define MAX_COAL_AT_POTTERY       (POTTERY_COAL_MAKE_GOODS*20)
#define MAX_JOBS_AT_POTTERY       (POTTERY_JOBS*20)
#define MAX_GOODS_AT_POTTERY      (POTTERY_MADE_GOODS*20)

#include "modules.h"
#include "../lintypes.h"
#include "../lctypes.h"

class PotteryConstructionGroup: public ConstructionGroup {
public:
    PotteryConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance, int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance,
        cost, tech, range, 2/*mps_pages*/
    )
    {
        commodityRuleCount[STUFF_JOBS].maxload = MAX_JOBS_AT_POTTERY;
        commodityRuleCount[STUFF_JOBS].take = true;
        commodityRuleCount[STUFF_JOBS].give = false;
        commodityRuleCount[STUFF_COAL].maxload = MAX_COAL_AT_POTTERY;
        commodityRuleCount[STUFF_COAL].take = true;
        commodityRuleCount[STUFF_COAL].give = false;
        commodityRuleCount[STUFF_GOODS].maxload = MAX_GOODS_AT_POTTERY;
        commodityRuleCount[STUFF_GOODS].take = false;
        commodityRuleCount[STUFF_GOODS].give = true;
        commodityRuleCount[STUFF_ORE].maxload = MAX_ORE_AT_POTTERY;
        commodityRuleCount[STUFF_ORE].take = true;
        commodityRuleCount[STUFF_ORE].give = false;
    }
    // overriding method that creates a pottery
    virtual Construction *createConstruction(int x, int y);
};

extern PotteryConstructionGroup potteryConstructionGroup;

class Pottery: public RegisteredConstruction<Pottery> { // Pottery inherits from its own RegisteredConstruction
public:
    Pottery(int x, int y, ConstructionGroup *cstgrp): RegisteredConstruction<Pottery>(x, y)
    {
        this->constructionGroup = cstgrp;
        init_resources();
        // this->anim = 0; // or real_time?
        this->pauseCounter = 0;
        this->busy = 0;
        this->working_days = 0;
        this->animate_enable = false;
        initialize_commodities();

        commodityMaxProd[STUFF_GOODS] = 100 * POTTERY_MADE_GOODS;
        commodityMaxCons[STUFF_ORE] = 100 * POTTERY_ORE_MAKE_GOODS;
        commodityMaxCons[STUFF_COAL] = 100 * POTTERY_COAL_MAKE_GOODS;
        commodityMaxCons[STUFF_JOBS] = 100 * POTTERY_JOBS;
    }
    virtual ~Pottery() { }
    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;

    int  anim;
    int  pauseCounter;
    int  working_days, busy;
    bool animate_enable;
};
