#define GROUP_BLACKSMITH_COLOUR (white(15))
#define GROUP_BLACKSMITH_COST   5000
#define GROUP_BLACKSMITH_COST_MUL 25
#define GROUP_BLACKSMITH_BUL_COST   1000
#define GROUP_BLACKSMITH_TECH   3
#define GROUP_BLACKSMITH_FIREC 60
#define GROUP_BLACKSMITH_RANGE 0
#define GROUP_BLACKSMITH_SIZE 2

#define BLACKSMITH_JOBS    35

#define BLACKSMITH_STEEL_USED 1
#define BLACKSMITH_COAL_USED  1
#define GOODS_MADE_BY_BLACKSMITH 50
#define MAX_JOBS_AT_BLACKSMITH (BLACKSMITH_JOBS*20)
#define MAX_COAL_AT_BLACKSMITH (BLACKSMITH_COAL_USED*20)
#define MAX_STEEL_AT_BLACKSMITH (BLACKSMITH_STEEL_USED*20)
#define MAX_GOODS_AT_BLACKSMITH (GOODS_MADE_BY_BLACKSMITH*20)
#define BLACKSMITH_CLOSE_TIME 25

#define BLACKSMITH_BATCH (GOODS_MADE_BY_BLACKSMITH*100)
//#define BLACKSMITH_ANIM_THRESHOLD 10
#define BLACKSMITH_ANIM_SPEED    200

#include "modules.h"
#include "../lintypes.h"
#include "../lctypes.h"

class BlacksmithConstructionGroup: public ConstructionGroup {
public:
    BlacksmithConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance,
        int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance,
        cost, tech, range, 2/*mps_pages*/
    )
    {
        commodityRuleCount[STUFF_JOBS].maxload = MAX_JOBS_AT_BLACKSMITH;
        commodityRuleCount[STUFF_JOBS].take = true;
        commodityRuleCount[STUFF_JOBS].give = false;
        commodityRuleCount[STUFF_COAL].maxload = MAX_COAL_AT_BLACKSMITH;
        commodityRuleCount[STUFF_COAL].take = true;
        commodityRuleCount[STUFF_COAL].give = false;
        commodityRuleCount[STUFF_STEEL].maxload = MAX_STEEL_AT_BLACKSMITH;
        commodityRuleCount[STUFF_STEEL].take = true;
        commodityRuleCount[STUFF_STEEL].give = false;
        commodityRuleCount[STUFF_GOODS].maxload = MAX_GOODS_AT_BLACKSMITH;
        commodityRuleCount[STUFF_GOODS].take = false;
        commodityRuleCount[STUFF_GOODS].give = true;
    }
    // overriding method that creates a blacksmith
    virtual Construction *createConstruction(int x, int y);
};

extern BlacksmithConstructionGroup blacksmithConstructionGroup;

class Blacksmith: public RegisteredConstruction<Blacksmith> { // Blacksmith inherits from its RegisteredConstruction
public:
    Blacksmith(int x, int y, ConstructionGroup *cstgrp): RegisteredConstruction<Blacksmith>(x, y)
    {
        this->constructionGroup = cstgrp;
        init_resources();
        this->anim = 0;
        this->pauseCounter = 0;
        this->busy = 0;
        this->working_days = 0;
        this->animate_enable = false;
        this->goods_made = 0;
        initialize_commodities();

        commodityMaxProd[STUFF_GOODS] = 100 * GOODS_MADE_BY_BLACKSMITH;
        commodityMaxCons[STUFF_COAL] = 100 * BLACKSMITH_COAL_USED;
        commodityMaxCons[STUFF_STEEL] = 100 * BLACKSMITH_STEEL_USED;
        commodityMaxCons[STUFF_JOBS] = 100 * BLACKSMITH_JOBS;
    }
    virtual ~Blacksmith() { }
    virtual void update() override;
    virtual void report() override;
    virtual void animate() override;

    int  goods_made;
    int  anim;
    int  pauseCounter;
    int  working_days, busy;
    bool animate_enable;
};


/** @file lincity/modules/blacksmith.h */
