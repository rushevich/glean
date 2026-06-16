#include <mupdf/fitz.h>

#include <print>
#include <stdexcept>

#include "wrapper/pdf.hpp"
int main() {
  glean::pdf pdf("cheatsheet.pdf");
  fz_try(pdf.ctx()) fz_save_pixmap_as_png(pdf.ctx(), pdf.render(0).get(), "cheatsheet.png");
  fz_catch(pdf.ctx()) { throw std::runtime_error(fz_caught_message(pdf.ctx())); }
  return 0;
}
