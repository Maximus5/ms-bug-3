# Coordinate system is broken in Windows 10

## The problem

Monitor's working area coordinate {0,0} does not conform left-top corner of the window anymore in Windows 10.
In other words, calling `SetWindowPos(hWnd, NULL, 0,0,0,0, SWP_NOSIZE)` leaves a gap at the left.


## Original report

The problem was reported in long ago in April 2015, when Windows 10 was not released yet to general public.
Since that time, there was neither official answer from Microsoft, nor workaround recommendations.

And here are links:

* [insider/forum/insider_wintp-insider_desktop/desktop-coordinate-system-is-broken](http://answers.microsoft.com/en-us/insider/forum/insider_wintp-insider_desktop/desktop-coordinate-system-is-broken/9e6fd9ab-6d27-45e0-bb55-4c868cd6ac45)
* [ConEmu Issue 284](https://github.com/Maximus5/ConEmu/issues/284)
* [Simple PowerShell script demonstrating the problem](https://gist.github.com/Maximus5/d6ef8119c25937aee6bc110fc50bfe5a)
* I belive, I reported the problem via feedback application, but I can't find this report now.


## Simple PowerShell script

**Requirements**

1. Windows 10 of course.
2. Task bar panel location is bottom or right edge of screen. Script does not check *working* area coordinates.

~~~
[void][reflection.assembly]::LoadWithPartialName("System.Windows.Forms")
$form = New-Object System.Windows.Forms.Form
$form.Text = "Hello World"
$set_pos = { $form.Location = New-Object System.Drawing.Point(0, 0); }
$form.add_Load($set_pos)
[void]$form.ShowDialog()
~~~

![Sample result](https://github.com/Maximus5/ms-bug-3/blob/master/PowerShellTest.jpg?raw=true)
