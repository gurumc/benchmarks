#include <benchmark/benchmark.h>

#include <algorithm>
#include <memory>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <iostream>

#include <cstdlib>

const std::string strs[] = {"M1", "M2", "M3", "M4", "M5", "M6"};
const std::string strs2[] = {"M1", "M1", "M2", "M2", "M3", "M3"};

void emplace_with_sort_no_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;
	std::map<std::string, std::map<std::string, bool>>::iterator lModelIt;

	for (auto _ : state) {
		auto lFirst = true;
		for(int i = 1; i <= 6; i++)
		{
			std::string s = "Model" + std::to_string(i);
			if (lFirst || s != lModelIt->first)
			{
				lFirst = false;
				lModelIt = m2.emplace(std::piecewise_construct, std::forward_as_tuple(s), std::forward_as_tuple()).first;
			}
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(emplace_with_sort_no_duplicates);

void emplace_with_sort_with_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;
	std::map<std::string, std::map<std::string, bool>>::iterator lModelIt;

	for (auto _ : state) {
		auto lFirst = true;
		for(int i = 2; i <= 7; i++)
		{
			std::string s = "Model" + std::to_string(i/2);
			if (lFirst || s != lModelIt->first)
			{
				lFirst = false;
				lModelIt = m2.emplace(std::piecewise_construct, std::forward_as_tuple(s), std::forward_as_tuple()).first;
			}
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(emplace_with_sort_with_duplicates);

void emplace_with_find_no_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;

	for (auto _ : state) {
		for(int i = 1; i <= 6; i++)
		{
			std::string s = "Model" + std::to_string(i);
			if (m2.find(s) == m2.end())
			{
				m2.emplace(std::piecewise_construct, std::forward_as_tuple(s), std::forward_as_tuple());
			}
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(emplace_with_find_no_duplicates);

void emplace_with_find_with_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;

	for (auto _ : state) {
		for(int i = 2; i <= 7; i++)
		{
			std::string s = "Model" + std::to_string(i/2);
			if (m2.find(s) == m2.end())
			{
				m2.emplace(std::piecewise_construct, std::forward_as_tuple(s), std::forward_as_tuple());
			}
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(emplace_with_find_with_duplicates);

void try_emplace_no_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;

	for (auto _ : state) {
		for(int i = 1; i <= 6; i++)
		{
			std::string s = "Model" + std::to_string(i);
			m2.try_emplace(s);
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(try_emplace_no_duplicates);

void try_emplace_with_duplicates(benchmark::State& state) {
	std::map<std::string, std::map<std::string, bool>> m2;
	for (auto _ : state) {
		for(int i = 2; i <= 7; i++)
		{
			std::string s = "Model" + std::to_string(i/2);
			m2.try_emplace(s);
		}

		state.PauseTiming();
		m2.clear();
		state.ResumeTiming();
	}
}

BENCHMARK(try_emplace_with_duplicates);

BENCHMARK_MAIN();
