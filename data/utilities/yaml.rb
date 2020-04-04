#!/usr/bin/env python
# -*- coding: utf-8 -*-

# RIM: Yaml
module Utilities
  require 'yaml'

  def read_yaml(path_file_yaml)
    # Read a Yaml File.
    begin
      
      return YAML.load(RFile.read(path_file_yaml)) || {}
    rescue => exception
      print "eE: ", path_file_yaml
      exit()
    end
    
  end
    
  def write_yaml(path_file_yaml, data)
    # Write a Yaml File.
    return RFile.write(path_file_yaml, YAML.dump(read_yaml(path_file_yaml)\
                                                            .update(data)))
    end
end