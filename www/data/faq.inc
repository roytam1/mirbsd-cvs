Title: Why don't I have colours on the console?

<p>The first virtual terminal is the system console, unless the
 system runs from serial console. Use Ctrl-Alt-F2 to switch to
 the second one, whose terminal type defaults to “wsvt25”, thus
 allowing colors and more advanced features.</p>
<p>This does not work on sparc, as there is only one virtual
 console on wsfb-using devices. You can, however, simply “export
 TERM=wsvtg” there, as the sparc system console, wsdisplay(4),
 emulates a colourful VT100/VT220 as well, in MirOS #10.</p>
----
