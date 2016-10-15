# Coordinate system is broken in Windows 10

## The problem

Monitor's working area coordinate {0,0} does not conform left-top corner of the window anymore in Windows 10.
In other words, calling `SetWindowPos(hWnd, NULL, 0,0,0,0, SWP_NOSIZE)` leaves a gap at the left.

![Sample result](https://github.com/Maximus5/ms-bug-3/blob/master/PowerShellTest.jpg?raw=true)

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


## C++ project (WinAPI)

Simple C++ project (you may download [binary from releases](https://github.com/Maximus5/ms-bug-3/releases)) demostrates the problem in details.
It takes into account active monitor working area and tries to move its window to the screen edges.

Just click the button, do you see the gap?

![Sample result](https://github.com/Maximus5/ms-bug-3/blob/master/WinApiGap.png?raw=true)

Well, lets move the window dragging its caption with mouse. Do you see **negative** coordinates in the caption?

Really? **Negative** coordinates of the **normal** (not maximized) window on the primary monitor?

![Sample result](https://github.com/Maximus5/ms-bug-3/blob/master/WinApiNegative.png?raw=true)


## The question

Personally, I consider this breaking change in coordinate system logic is a bug.
But it would be nice to recieve a feedback from Microsoft.

* Is it a confirmed bug?
* Is it a ‘feature’?
* Is there any workaround to put the window at the edge of the monitor working area?
