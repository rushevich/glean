#include "wrapper/context.hpp"
#include "wrapper/document.hpp"
#include "wrapper/pixmap.hpp"
#include <mupdf/fitz.h>
#include <print>
#include <stdexcept>
int main() {
    using namespace glean;

    context ctx;
    std::println("Created new context successfully");

    document doc {ctx, "cheatsheet.pdf"};
    std::println("Created new document successfully");

    pixmap pm = render_page(doc, 0);
    std::println("Rendered page successfully... spitting out samples");

    fz_try(ctx.get())
        fz_save_pixmap_as_png(ctx.get(), pm.get(), "cheatsheet.png");
    fz_catch(ctx.get()) {
        throw std::runtime_error(fz_caught_message(ctx.get()));
    }
    return 0;
}
