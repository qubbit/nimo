## How to build

```
cd ext/nimo
ruby extconf.rb
make
cd ../..
```

## Test
```
ruby -Ilib:ext -r nimo/nimo -e 'Nimo::Macintosh.display_alert_panel("Hello", "World")'
```
