require 'test/unit'
require 'hin16'

class TC_FXRegistry < Test::Unit::TestCase
  include Fox

  def setup
    @reg = FXRegistry.new("TC_FXRegistry", "Hinamori")
  end

  def test_boolEntries
    assert(@reg.writeBoolEntry("SETTINGS", "trueEntry", true))
    assert(@reg.writeBoolEntry("SETTINGS", "falseEntry", false))

    assert(@reg.readBoolEntry("SETTINGS", "trueEntry"))
    assert(@reg.readBoolEntry("SETTINGS", "trueEntry", true))
    assert(@reg.readBoolEntry("SETTINGS", "trueEntry", false))

    assert(!@reg.readBoolEntry("SETTINGS", "falseEntry"))
    assert(!@reg.readBoolEntry("SETTINGS", "falseEntry", true))
    assert(!@reg.readBoolEntry("SETTINGS", "falseEntry", false))

    assert(!@reg.readBoolEntry("SETTINGS", "missingEntry"))
    assert(!@reg.readBoolEntry("SETTINGS", "missingEntry", false))
    assert( @reg.readBoolEntry("SETTINGS", "missingEntry", true))
  end
end
