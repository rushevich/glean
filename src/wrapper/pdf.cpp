#include "wrapper/pdf.hpp"

#include "wrapper/context.hpp"
#include "wrapper/document.hpp"
#include "wrapper/pixmap.hpp"

namespace glean {
    pdf::pdf(const char* path) : _ctx(), _doc(_ctx, path), _page_count(_doc.page_count()) {}

    // pdf::~pdf() = default;
    //
    // pdf::pdf(pdf&& other) : _ctx(std::move(other._ctx)), _doc(std::move(other._doc)) {}
    //
    // pdf& pdf::operator=(pdf&& other) {
    //     if (this != &other) {
    //     }
    //     return *this;
    // }

    pixmap pdf::render(int page_number, float zoom, float rotate) {
        return render_page(_doc, page_number, zoom, rotate);
    }

}  // namespace glean
