try {
    $s7com = New-Object -ComObject "Simatic.Simatic.1"
    Write-Output "COM object loaded successfully."
} catch {
    Write-Output "Failed to load COM object: $_"
}