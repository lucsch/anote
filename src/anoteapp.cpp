#include "anoteapp.h"

#include "anoteframe.h"

IMPLEMENT_APP(AnoteApp)

bool AnoteApp::OnInit() {
  if (!wxApp::OnInit()) {
    return false;
  }

  AnoteFrame *frame = new AnoteFrame("Minimal wxWidgets App");
  frame->Show(true);
  return true;
}