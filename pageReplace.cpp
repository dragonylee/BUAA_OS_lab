#pragma GCC optimize(2)
#include "pageReplace.h"
#define MAX_PHY_PAGE 64

int clock = 0;                   // 时间戳
char where[1050000];             // 记录某个虚拟页面所在的物理页框(+1)，与physic_memery互逆
int last_time[MAX_PHY_PAGE + 5]; // 记录每个物理页框最近一次访问的时间戳

// LRU算法
void pageReplace(long *physic_memery, long nwAdd)
{
    long page = nwAdd >> 12;

    if (clock < MAX_PHY_PAGE) // 表示物理页框还有空余
    {
        if (where[page])
            last_time[where[page] - 1] = clock;
        else
        {
            physic_memery[clock] = page;
            where[page] = (char)clock + 1;
            last_time[clock] = clock++;
        }
        return;
    }

    ++clock;

    if (where[page]) // page在物理页框中，更新时间戳
    {
        last_time[where[page] - 1] = clock;
    }
    else // 寻找最小的时间戳（最久未使用）的index，替换页面
    {
        int idx = 0, temp = 1 << 30;
        for (register int i = 0; i < MAX_PHY_PAGE; ++i)
            if (last_time[i] < temp)
                temp = last_time[i], idx = i;

        where[physic_memery[idx]] = 0;
        where[page] = (char)idx + 1;
        physic_memery[idx] = page;
        last_time[idx] = clock;
    }
}

