#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

module Utilities
  class RFile < File
    def self.append(file, data)
      f = self.open(file, 'a')
      f.write(data)
      f.close()
    end

    def self.dir?(path)
      return directory?(path)
    end
  end
end