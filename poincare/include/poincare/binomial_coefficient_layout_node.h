#ifndef POINCARE_BINOMIAL_COEFFICIENT_LAYOUT_NODE_H
#define POINCARE_BINOMIAL_COEFFICIENT_LAYOUT_NODE_H

#include <poincare/layout_cursor.h>
#include <poincare/layout_node.h>
#include <poincare/layout_reference.h>
#include <poincare/grid_layout_node.h>

namespace Poincare {

class BinomialCoefficientLayoutNode : public LayoutNode {
public:
  using LayoutNode::LayoutNode;

  // LayoutNode
  void moveCursorLeft(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void moveCursorRight(LayoutCursor * cursor, bool * shouldRecomputeLayout) override;
  void moveCursorUp(LayoutCursor * cursor, bool * shouldRecomputeLayout, bool equivalentPositionVisited = false) override;
  void moveCursorDown(LayoutCursor * cursor, bool * shouldRecomputeLayout, bool equivalentPositionVisited = false) override;

  // SerializableNode
  int writeTextInBuffer(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;

  // TreeNode
  // size() does not need to be overrided
  int numberOfChildren() const override { return 2; }
#if TREE_LOG
  const char * description() const override { return "BinomialCoefficientLayout"; }
#endif

protected:
  // LayoutNode
  void computeSize() override;
  void computeBaseline() override;
  KDPoint positionOfChild(LayoutNode * child) override;
private:
  KDCoordinate knHeight() { return nLayout()->layoutSize().height() + GridLayoutNode::k_gridEntryMargin + kLayout()->layoutSize().height(); }
  void render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) override;
  LayoutNode * nLayout() { return childAtIndex(0); }
  LayoutNode * kLayout() { return childAtIndex(1); }
};

class BinomialCoefficientLayoutRef : public LayoutReference {
public:
  BinomialCoefficientLayoutRef(LayoutRef n, LayoutRef k) :
    BinomialCoefficientLayoutRef()
  {
    addChildTreeAtIndex(n, 0, 0);
    addChildTreeAtIndex(k, 1, 1);
  }
  BinomialCoefficientLayoutRef(TreeNode * n) : LayoutReference(n) {}
private:
  BinomialCoefficientLayoutRef() : LayoutReference() {
    TreeNode * node = TreePool::sharedPool()->createTreeNode<BinomialCoefficientLayoutNode>();
    m_identifier = node->identifier();
  }
};

}

#endif
