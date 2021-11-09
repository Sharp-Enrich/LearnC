package main

import (
	"embed"
	"flag"
	"fmt"
	"io/fs"
	"log"
	"net/http"
	"os"
)

//go:embed site/*
var doc embed.FS

func usage() {
	fmt.Fprintf(os.Stderr, `learnc 学习C语言的笔记.
usage: learnc [-public] [-port <端口>]
options:
`)
	flag.PrintDefaults()
	fmt.Fprintf(os.Stderr, `
examples:

$learnc                    默认单击访问127.0.0.1:3000
$learnc -public            可外部访问，默认3000端口
$learn -public -port 8000  可外部访问，8000端口

`)
	os.Exit(2)
}

var (
	public = flag.Bool("public", false, "是否允许外部访问")
	port   = flag.Int("port", 3000, "指定服务端口")
)

func main() {
	flag.Usage = usage
	flag.Parse()
	ip := "127.0.0.1"
	if *public {
		ip = "0.0.0.0"
	}
	f, _ := fs.Sub(doc, "site")
	http.Handle("/", http.FileServer(http.FS(f)))
	log.Printf("本机请用浏览器访问http://127.0.0.1:%d", *port)
	if *public {
		log.Printf("公网请用浏览器访问http://本机局域网或公网IP:%d", *port)
	} else {
		log.Println("仅可本地访问，不能外网访问")

	}
	log.Fatal(http.ListenAndServe(fmt.Sprintf("%s:%d", ip, *port), nil))
}
