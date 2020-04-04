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

  def coding(text, code)
    #Encoding.name_list[]
    begin
      return text.encode(Encoding.name_list[code]) if code.is_a?(Integer)
      return text.encode(code) if code.is_a?(String)
    rescue Encoding::ConverterNotFoundError
      return nil
    rescue Encoding::UndefinedConversionError
      return nil
      # "Code: #{code} not in list of local codes."
    end
  end
end