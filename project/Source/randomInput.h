#pragma once
#include <random>

class Random {
public:
    Random() : rng(std::random_device{}()) {}
    //値を固定(デバック用)
    Random(const int& seed) : rng(seed) {}

    /// <summary>
    /// 乱数を生成
    /// </summary>
    /// <param name="min">生成する乱数の最小値</param>
    /// <param name="max">生成する乱数の最大値</param>
    /// <returns>生成した乱数</returns>
    const int Input(const int& min, const int& max) 
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }


private:
    std::mt19937 rng;
};
