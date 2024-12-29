- show all process  of fdf

```sh
watch -n 1 "ps aux | grep fdf | grep -v grep"
```

- kill all fdf

```sh
kill $(ps aux | grep fdf | grep -v grep | awk '{print $2}')
```

- run all fdf

```sh
for i in $(find maps/monochro/*.fdf)
do
   echo "Current model: $i";
   ./fdf $i || echo "Failed on: $i" >&2
done
```
