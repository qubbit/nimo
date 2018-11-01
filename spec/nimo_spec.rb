require 'nimo/nimo'
require 'test/unit'

module Nimo
  class TestMacintosh < Test::Unit::TestCase
    def test_display_alert_panel
      assert_nothing_raised do
        retval = Nimo::Macintosh.display_alert_panel('foo', 'bar')
        assert(retval == nil)
      end
    end
  end
end
