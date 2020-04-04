#!/usr/bin/env python
# -*- coding: utf-8 -*-

from tkinter import Tk, Menu, PanedWindow, Label, Button, Frame, Text, Scrollbar


class YuriWindow(Tk):

    def __init__(self, title='Choeditor', ClassName='Choeditor'):
        super().__init__(ClassName)
        self.title(title)
        #self.wm_protocol('WM_DELETE_WINDOW', self._destroy)
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)
        self.grid_columnconfigure(1, minsize=90, weight=1)
        self.grid_columnconfigure(2, minsize=90, weight=1)
        self.grid_columnconfigure(3, minsize=90, weight=1)

        self.mBar = Menu(self, relief='raised', borderwidth=2)

        self['menu'] = self.mBar

        pane = PanedWindow(orient='horizontal', sashwidth=5,
                           sashrelief='solid', bg='#ddd')
        pane.add(self.makeTextFrame(pane))
        #pane.add(self.makeGraphFrame(pane))
        pane.grid(row=0, columnspan=4, sticky='news')

        self.output_lbl = Label(self, height= 1, text=" --- ", bg="#ddf",
                                font=("Arial", 16, 'normal'), borderwidth=2,
                                relief="ridg")
        self.start_btn = Button(self, text=" START ", font=None,
                                fg="white", disabledforeground = "#fed")  # command=self.startDemo
        self.stop_btn = Button(self, text=" STOP ", font=None,
                               fg="white", disabledforeground = "#fed")  # command=self.stopIt
        self.clear_btn = Button(self, text=" CLEAR ", font=None,
                                fg="white", disabledforeground="#fed")  # command = self.clearCanvas

        self.output_lbl.grid(row=1, column=0, sticky='news', padx=(0,5))
        self.start_btn.grid(row=1, column=1, sticky='ew')
        self.stop_btn.grid(row=1, column=2, sticky='ew')
        self.clear_btn.grid(row=1, column=3, sticky='ew')
        """
        Percolator(self.text).insertfilter(ColorDelegator())
        self.dirty = False
        self.exitflag = False
        if filename:
            self.loadfile(filename)
        self.configGUI(DISABLED, DISABLED, DISABLED,
                       "Choose example from menu", "black")
        self.state = STARTUP
        """
    
    def makeTextFrame(self, root):
        self.text_frame = text_frame = Frame(root)
        self.text = text = Text(text_frame, name='text', padx=5,
                                wrap='none', width=45)
        #color_config(text)

        self.vbar = vbar = Scrollbar(text_frame, name='vbar')
        vbar['command'] = text.yview
        vbar.pack(side='left', fill='y')
        self.hbar = hbar = Scrollbar(text_frame, name='hbar', orient='horizontal')
        hbar['command'] = text.xview
        hbar.pack(side='bottom', fill='x')
        text['yscrollcommand'] = vbar.set
        text['xscrollcommand'] = hbar.set

        #text['font'] = None
        shortcut = 'Control'
        """
        text.bind_all('<%s-minus>' % shortcut, self.decrease_size)
        text.bind_all('<%s-underscore>' % shortcut, self.decrease_size)
        text.bind_all('<%s-equal>' % shortcut, self.increase_size)
        text.bind_all('<%s-plus>' % shortcut, self.increase_size)
        text.bind('<Control-MouseWheel>', self.update_mousewheel)
        text.bind('<Control-Button-4>', self.increase_size)
        text.bind('<Control-Button-5>', self.decrease_size)
        """

        text.pack(side='left', fill='both', expand=1)
        return text_frame

    def makeGraphFrame(self, root):
        #turtle._Screen._root = root
        self.canvwidth = 1000
        self.canvheight = 800
        #oot._Screen._canvas = self._canvas = canvas = root.ScrolledCanvas(
        #        root, 800, 600, self.canvwidth, self.canvheight)
        #root.adjustScrolls()
        #root._rootwindow.bind('<Configure>', self.onResize)
        #root._canvas['borderwidth'] = 0

        #self.screen = _s_ = root.Screen()
        #root.TurtleScreen.__init__(_s_, _s_._canvas)
        #self.scanvas = _s_._canvas
        #root.RawTurtle.screens = [_s_]
        return canvas

# graphics -> Yuri
asd = YuriWindow()
asd.mainloop()