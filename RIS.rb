#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# ------------------------------------------------------------
# This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# If it is not possible or desirable to put the notice in a particular
# file, then You may include the notice in a location (such as a LICENSE
# file in a relevant directory) where a recipient would be likely to look
# for such a notice.
#
# You may add additional accurate notices of copyright ownership.
#
# Exhibit B - "Incompatible With Secondary Licenses" Notice

require_relative 'data/centersystem'

class RIS

  def initialize()
    @log = ""

  end
  def activate()
    start()
  end
end

def main()
  app = RIS.new()
  app.activate()
end
op = [10]
def sopa(l)
  print(l, "\n")
  l[0] -= 1
end

sopa(op) while op[0] != 5

if __FILE__ == $0
  #main()
end

__END__
class FileNotFound < StandardError
  def initialize(safe_to_retry = false, message = 'Something went wrong')
    @safe_to_retry = safe_to_retry
    super(message)
  end
  
  def method_missing(method, *args, &block)
    "Cannot call #{method} on Animal"
  end
end

#app = RIS.new()
# gem 'mini_portile2', '~>2.1'
# sh / rake
#RUBY_PLATFORM
mastodown / mastodonte redsocial