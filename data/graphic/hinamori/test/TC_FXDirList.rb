require 'test/unit'
require 'testcase'
require 'hin16'

class TC_FXDirList < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    @dirList = FXDirList.new(mainWindow)
  end

  def test_setCurrentFile
    file = ""
    @dirList.setCurrentFile(file)
    @dirList.setCurrentFile(file, true)
  end

  def test_setDirectory
    path = ""
    @dirList.setDirectory(path)
    @dirList.setDirectory(path, true)
  end

  def test_getPathnameItem
    path = ""
    @dirList.getPathnameItem(path)
  end
end

