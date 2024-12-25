- show all process  of fdf

```sh
watch -n 1 "ps aux | grep fdf | grep -v grep"
```

- kill all fdf

```sh
kill $(ps aux | grep fdf | grep -v grep | awk '{print $2}')
```
