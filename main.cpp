#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// Test Case base class
class TestCase {
public:
    virtual void run() = 0;
    virtual std::string name() = 0;
};

// Benchmark Suite class
class Benchmark {
public:
    void add_case(TestCase* tc) {
        cases.push_back(tc);
    }

    void run() {
        for (auto tc : cases) {
            std::cout << "Running " << tc->name() << "...\n";
            auto start_time = std::chrono::high_resolution_clock::now();
            tc->run();
            auto end_time = std::chrono::high_resolution_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            std::cout << tc->name() << " elapsed time: " << elapsed_time << " us\n\n";
        }
    }

private:
    std::vector<TestCase*> cases;
};

// Timer class
class Timer {
public:
    Timer() {
        reset();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    int elapsed_us() {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};

// Reporter class
class Reporter {
public:
    void report(const std::string& name, int elapsed_time) {
        std::cout << name << " elapsed time: " << elapsed_time << " us\n";
    }
};

// Example test case
class ExampleTestCase : public TestCase {
public:
    void run() override {
        Timer timer;
        // do something to be benchmarked
        for (int i = 0; i < 1000000; i++) {
            int a = 1 + 1;
        }
        reporter.report(name(), timer.elapsed_us());
    }

    std::string name() override {
        return "Example Test Case";
    }

private:
    Reporter reporter;
};

int main() {
    Benchmark bench;
    bench.add_case(new ExampleTestCase());
    bench.run();
    return 0;
}
