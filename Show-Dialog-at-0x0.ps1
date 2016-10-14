[void][reflection.assembly]::LoadWithPartialName("System.Windows.Forms")
$form = New-Object System.Windows.Forms.Form
$form.Text = "Hello World"
$set_pos = { $form.Location = New-Object System.DrawingPoint(0,0); }
$form.add_Load($set_pos)
[void]$form.ShowDialog()
