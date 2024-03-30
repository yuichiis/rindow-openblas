<?php
namespace RindowTest\OpenBLAS;
require_once __DIR__.'/AbstractNDArrayPhp.php';
require_once __DIR__.'/../testPHP/HostBuffer.php';
if(version_compare(phpversion(),'8.0.0','<')) {
    require_once __DIR__.'/../testPHP/NDArrayPhp7.php';
} else {
    require_once __DIR__.'/../testPHP/NDArrayPhp8.php';
}

use Interop\Polite\Math\Matrix\NDArray;
use TypeError;
use InvalidArgumentException;
use RindowTest\OpenBLAS\NDArrayPhp;

function R(
    int $start,
    int $limit
) : Range
{
    if(func_num_args()!=2) {
        throw new InvalidArgumentException('R must have only two arguments: "start" and "limit".');
    }
    return new Range($limit,$start);
}

class Range
{
    protected $start;
    protected $limit;
    protected $delta;

    public function __construct(
        $limit,
        $start=null,
        $delta=null)
    {
        $this->limit = $limit;
        $this->start = $start ?? 0;
        $this->delta = $delta ?? (($limit>=$start)? 1 : -1);
    }

    public function start()
    {
        return $this->start;
    }

    public function limit()
    {
        return $this->limit;
    }

    public function delta()
    {
        return $this->delta;
    }
}

trait Utils
{
    public function zeros(array $shape,int $dtype=null)
    {
        $ndarray = $this->array(null,$dtype,$shape);
        $buffer = $ndarray->buffer();
        $size = $buffer->count();
        for($i=0;$i<$size;$i++) {
            $buffer[$i] = 0;
        }
        return $ndarray;
    }

    public function ones(array $shape,int $dtype=null)
    {
        $ndarray = $this->array(null,$dtype,$shape);
        $buffer = $ndarray->buffer();
        $size = $buffer->count();
        for($i=0;$i<$size;$i++) {
            $buffer[$i] = 1;
        }
        return $ndarray;
    }

    public function zerosLike(object $ndarray)
    {
        return $this->zeros($ndarray->shape(),$ndarray->dtype());
    }

    public function arange(int $count ,$start=null, $step=null, $dtype=null)
    {
        if($start===null)
            $start = 0;
        if($step===null)
            $step = 1;
        if($dtype===null) {
            if(is_int($start))
                $dtype = NDArray::int32;
            else
                $dtype = NDArray::float32;
        }
        $array = $this->zeros([$count], $dtype);
        $buffer = $array->buffer();
        $n = $start;
        for($i=0; $i<$count; $i++) {
            $buffer[$i] = $n;
            $n += $step;
        }
        return $array;
    }

    public function array($array=null, int $dtype=null, array $shape=null) : object
    {
        $ndarray = new NDArrayPhp($array, $dtype, $shape);
        return $ndarray;
    }


    public function getMatlibVersion($matlib)
    {
        $config = $matlib->getConfig();
        if(strpos($config,'Matlib')===0) {
            $config = explode(' ',$config);
            return $config[1];
        } else {
            return '0.0.0';
        }
    }

    public function checkSkip($mark)
    {
        if(!in_array($mark,[
            //'multiply',
            //'duplicate'
            ])) {
            return false;
        }
        $this->markTestSkipped($mark);
        return true;
    }


    public function sum($n,$X,$offsetX,$incX)
    {
        $a = 0;
        for($i=0;$i<$n;$i++) {
            $a += $X[$offsetX+$i*$incX];
        }
        return $a;
    }

    protected function printableShapes($values)
    {
        if(!is_array($values)) {
            if($values instanceof NDArray)
                return '('.implode(',',$values->shape()).')';
            if(is_object($values))
                return '"'.get_class($values).'"';
            if(is_numeric($values) || is_string($values))
                return strval($values);
            return gettype($values);
        }
        $string = '[';
        foreach($values as $value) {
            if($string!='[') {
                $string .= ',';
            }
            $string .= $this->printableShapes($value);
        }
        $string .= ']';
        return $string;
    }

    protected function argExpectException($class)
    {
        if(version_compare(phpversion(),'8.1.0','<')) {
            $this->expectException(TypeError::class);
        } else {
            $this->expectException($class);
        }
    }

    protected function argExpectExceptionMessage($message)
    {
        if(version_compare(phpversion(),'8.1.0','<')) {
            $this->expectExceptionMessage('Argument ');
        } else {
            $this->expectExceptionMessage($message);
        }
    }
}