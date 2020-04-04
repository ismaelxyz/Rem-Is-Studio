#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

require_relative 'utilities'
include Utilities

# Main func
def start()
	require_relative 'dataversion'
	require_relative 'config/config'
	
	m = Config.see_config_data('u', 'Mode')[0]
	gs = Config.see_config_data('a', 'GraphicSupport')[0]

	if m == 'Graphic' || m.nil?() && gs
	   require_relative 'graphic/centersystem'
	   config = config_of_graphics()
	else
		config = Config.new()
	end
	config.load_all()
	#config.app('FilesTypes')
	print Utilities::name
	#['ListUser']
	#lan = Idiom.new(config.app['ExtensionsDir'])
	#print(lan.translate(["file open", "/copy"], ['edit'], 'go ', '/...'))
end