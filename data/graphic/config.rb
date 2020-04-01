#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# utilize: Config from data/graphic/config.rb


class GC < Config
    # Graphic Load Config
    def initialize()
        super()
        # Translate to japanese [Malvada rem, asesina noctuna]
        @info_user.update({'Theme' => 'Evil Rem',
                           'IconPack' => 'Assassins night'})
    end
end