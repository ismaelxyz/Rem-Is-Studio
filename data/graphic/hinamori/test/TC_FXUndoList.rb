require 'test/unit'
require 'hin16'
require 'hin16/undolist'

class DummyCommand < Fox::FXCommand
  def undo ; end
  def redo ; end
  def undoName
    "My Undo Name"
  end
  def redoName
    "My Redo Name"
  end
end

class TC_FXUndoList < Test::Unit::TestCase
  include Fox

  def test_cut_with_nil_marker
    undoList = FXUndoList.new
    assert_nothing_raised {
      undoList.cut
    }
  end

  def test_undoName
    undoList = FXUndoList.new
    assert_nil(undoList.undoName)
    c = DummyCommand.new
    undoList.add(c)
    assert_equal(c.undoName, undoList.undoName)
  end

  def test_redoName
    undoList = FXUndoList.new
    assert_nil(undoList.redoName)
    c = DummyCommand.new
    undoList.add(c)
    undoList.undo
    assert_equal(c.redoName, undoList.redoName)
  end
end

