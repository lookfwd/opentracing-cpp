#include <app_tracing.h>

/**
 * To run:
 * clear && g++ -I. -D__USE_XOPEN2K8 main.cpp build/opentracing/libopentracing.a -o main && ./main
 */
int main()
{
    // Setup
    ZipkinV1 t1;
    ZipkinV2 t2;

    MyHotTracer imp(t1, t2);

    GlobalTracer::install(&imp);


    {
        // Application code
        auto tracer = Cpp11GlobalTracer::instance();

        auto span = tracer.start("hi");

        std::vector<opentracing::TextMapPair> pairs;

        tracer.inject(&pairs, *span);

        auto ctx = tracer.extract(pairs);
    }

    // Cleanup
    GlobalTracer::uninstall();

    return 0;
}
