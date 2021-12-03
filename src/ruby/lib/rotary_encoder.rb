class RotaryEncoder
 def initialize(pin_a, pin_b)
    puts "Initializing RotaryEncoder ..."
    @pin_a = pin_a
    @pin_b = pin_b
    @rotation = 0
    @partner = 0b11110111
    @split_left = true
    @proc = []
    @proc_cnt = 0
  end

  def init_pins
    init_encoder(@pin_a, @pin_b)
  end

  def left?
    @split_left
  end

  def right?
    !@split_left
  end

  def configure(symbol)
    case symbol
    when :left
      @split_left = true
    when :right
      @split_left = false
    end
  end

  attr_accessor :split_left

  def read
    @rotation += read_encoder(@pin_a, @pin_b)
  end

  def clockwise(&block)
    @proc.push(block)
  end

  def call_cw
    @proc[@proc_cnt].call
  end
  def call_ccw
    @proc[@proc_cnt].call
  end

  def call_proc_if(num)
    if num == @partner
      @proc_cnt += 1
      if(@proc.size <= @proc_cnt)
        @proc_cnt = 0
      end
    elsif num > @partner
      @proc_cnt -= 1
      if(0 > @proc_cnt)
        @proc_cnt = @proc.size - 1
      end
    end
    @proc[@proc_cnt].call
  end

  def consume_rotation_anchor
    # ignore values of 1 and -1
    if @rotation > 1 && @proc
      @proc_cnt += 1
      if(@proc.size <= @proc_cnt)
        @proc_cnt = 0
      end
      @proc[@proc_cnt].call
      sleep_ms 20
    elsif @rotation < -1 && @proc
      @proc_cnt -= 1
      if(0 > @proc_cnt)
        @proc_cnt = @proc.size - 1
      end
      @proc[@proc_cnt].call
      # counterclockwise seems more sensitive
      sleep_ms 40
    end
    @rotation = 0
  end

  def consume_rotation_partner
    # ignore values of 1 and -1
    if @rotation > 1 && @proc
      res = @partner
      @proc_cnt += 1
      if(@proc.size <= @proc_cnt)
        @proc_cnt = 0
      end
      @proc[@proc_cnt].call
    elsif @rotation < -1 && @proc
      res = 1 + @partner
      @proc_cnt -= 1
      if(0 > @proc_cnt)
        @proc_cnt = @proc.size - 1
      end
      @proc[@proc_cnt].call
    else
      res = 0
    end
    @rotation = 0
    return res
  end
end
