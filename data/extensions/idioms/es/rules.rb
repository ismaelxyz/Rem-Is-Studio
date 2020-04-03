#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# Author: Ismael Belisario <ismaelbeli.com@gmail.com>
# This file from of: https://github.com/ismaelxyz
# Name Clave: RIS-ES-O

#Copyright © 2020 Ismael Belisario

#This file is part of Rem Is Studio.

#Rem Is Studio is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#Rem Is Studio is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this Rem Is Studio.  If not, see <https://www.gnu.org/licenses/>.
# IS 
class Rules
    attr_writer :wor

    def initialize(language)
        @word = nil
        @language = language
    end

    def el_la(num)
        if @language[@wor[num + 1]][-1] == 'o'
            return @language[@wor[num]] + ' el'
        elsif @language[@wor[num + 1]][-1] == 'a'
            return @language[@wor[num]] + ' la'
        end
    end

    def o_or_a(num)
        return @language[@wor[num]][..-2] + @language[@wor[num + 1]][-1]
    end
end

class ControlRules < Rules
    
    def initialize(language)
        super(language)
    end

    def translate(num)
        word = nil
        if @wor.size > 1
            word = if @wor[num] == '$new'
                    self.o_or_a(num)
                  elsif @wor[num] == '$open'
                    self.el_la(num)
                   end
        end
        word = @language[@wor[num]] if wor.nil?
        word += ' ' if @wor[num + 1] != '$...' and not @wor[num + 1].nil?
        return wor
    end 
end

module StartRules

    class ApplyRules
        attr_reader :language
        
        def initialize()
            @language = load_yaml(__dir__ + '/es.yaml')
            @cr = ControlRules.new(@language) 
        end

        def search_wor(*keyword)
            greatword = ""
            @cr.word = keyword

            keyword.each_index{|num|
                greatword += @cr.translate(num)
            }
            return greatWor
        end
    end
end