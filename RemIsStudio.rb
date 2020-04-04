#!/usr/bin/env ruby
# -*- coding: cp850 -*-

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
require_relative 'data/argv' 
#require_relative 'data/centersystem'


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
# Vars of Ruby
__ENCODING__, __FILE__, RUBY_PLATFORM, RUBY_VERSION, global_variables
module Chatty
  def self.method_added(method_name)
    puts "Adding #{method_name.inspect}"
  end
  def self.some_class_method() end
  def some_instance_method() end
end

module Chatty
  def self.method_removed(method_name)
    puts "Removing #{method_name.inspect}"
  end
  def self.some_class_method() end
  def some_instance_method() end
  class << self
    remove_method :some_class_method
  end
  remove_method :some_instance_method
end

module Chatty
  def self.method_added(method_name)
    puts "Adding #{method_name.inspect}\n"
  end
  def self.some_class_method() end
  def some_instance_method() end
  def sopa() end
end

module A
  def A.included(mod)
    puts "#{self} included in #{mod}"
  end
end
module Enumerable
  include A
end
 # => prints "A included in Enumerable"

 module A
  def self.extended(mod)
    puts "#{self} extended in #{mod}"
  end
end
module Enumerable
  extend A
end
 # => prints "A extended in Enumerable"

 module Picky
  def Picky.extend_object(o)
    if String === o
      puts "Can't add Picky to a String"
    else
      puts "Picky added to #{o.class}"
      super
    end
  end
end
(s = Array.new).extend Picky  # Call Object.extend
(s = "quick brown fox").extend Picky

produces:

Picky added to Array
Can't add Picky to a String'
class Thing
end
Thing.class_exec{
  def hello() "Hello there!" end
}
puts Thing.new.hello() 