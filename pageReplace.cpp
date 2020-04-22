#include "pageReplace.h"
#include <set>
#include <unordered_map>
using namespace std;
#define MAX_PHY_PAGE 64

// LRU算法
void pageReplace(long *physic_memery, long nwAdd)
{
    static int clock = 0;                   // 时间戳
    static unordered_map<long, int> where;  // 记录某个虚拟页面所在的物理页框，与physic_memery互逆
    static int last_time[MAX_PHY_PAGE + 5]; // 记录每个物理页框最近一次访问的时间戳
    long page = nwAdd >> 12;

    if (where.size() < MAX_PHY_PAGE) // 表示物理页框还有空余
    {
        if (where.count(page))
            last_time[where[page]] = clock;
        else
        {
            physic_memery[clock] = page;
            where[page] = clock;
            last_time[clock] = clock++;
        }
        return;
    }

    clock++;

    if (where.count(page)) // page在物理页框中，更新时间戳
    {
        last_time[where[page]] = clock;
    }
    else // 寻找最小的时间戳（最久未使用）的index，替换页面
    {
        int idx = 0, temp = 1 << 30;
        for (int i = 0; i < MAX_PHY_PAGE; i++)
            if (last_time[i] < temp)
                temp = last_time[i], idx = i;

        where.erase(physic_memery[idx]);
        where[page] = idx;
        physic_memery[idx] = page;
        last_time[idx] = clock;
    }
}

