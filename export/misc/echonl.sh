echonl(){
case "`uname -m`" in
  sun*)
    case "`uname -r`" in
      4.*)
        /bin/echo -n "$1"
        ;;
      5.*)
        /bin/echo "$1\c"
        ;;
      *)
        echo "Unsupported SunOS"
	exit 1
        ;;
    esac
    ;;
  9000/[347]??)
    echo "$1\c"
    ;;
  i?86)
    echo -n "$1"
    ;;
  IP22)
    echo -n "$1"
    ;;
  *)
    echo "$0: Unsupported OS"
    exit 1
    ;;
esac
}
